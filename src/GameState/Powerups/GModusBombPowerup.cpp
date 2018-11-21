#include "GModusBombPowerup.h"
//#include "GGameState.h"
#include "Game.h"

static ANIMSCRIPT BombAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP1(IMG_POWERUP_MODUS_BOMB),
  ASTEP1(IMG_POWERUP_MODUS_BOMB + 1),
  ALOOP
};

static ANIMSCRIPT BombDropAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ASTEP1(IMG_POWERUP_MODUS_BOMB + 2),
  ASTEP1(IMG_POWERUP_MODUS_BOMB + 3),
  ASTEP1(IMG_POWERUP_MODUS_BOMB + 4),
  ASTEP1(IMG_POWERUP_MODUS_BOMB + 5),
  ASTEP1(IMG_POWERUP_MODUS_BOMB + 6),
  ANULL(1),
  AEND
};

GModusBombPowerup::GModusBombPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : BPowerup(aSprite, aGameState) {
  mPlayerSprite->mBlockSize = BLOCKSIZE_1x1;
  mPlayerSprite->StartAnimation(BombAnimation);
  mState = STATE_MOVE;
}

GModusBombPowerup::~GModusBombPowerup() {

}

TBool GModusBombPowerup::Drop() {
  // disable rendering
  mPlayerSprite->flags &= ~SFLAG_RENDER;

  // where on the board the bomb was placed
  mBombRow = mPlayerSprite->BoardRow();
  mBombCol = mPlayerSprite->BoardCol();

  mBombStep  = 0;  // animation step
  mBombTimer = 1; // 1st step immediately

  return EFalse;
}

TBool GModusBombPowerup::StateMove() {
  mRepeatTimer--;

  if (TimedControl(JOYLEFT)) {
    MoveLeft();
  } else if (TimedControl(JOYRIGHT)) {
    MoveRight();
  } else if (TimedControl(JOYUP)) {
    MoveUp();
  } else if (TimedControl(JOYDOWN)) {
    MoveDown();
  }

  if (gControls.WasPressed(BUTTON_SELECT)) {
    Drop();
    mState = STATE_REMOVE;
    mPlayerSprite->StartAnimation(BombDropAnimation);
  }

  return ETrue;
}

class EmptyExplosion : public BProcess {
public:
  EmptyExplosion(TInt aRow, TInt aCol, GGameState *aGameState) : BProcess() {
    mSprite = new BAnimSprite(0, COMMON_SLOT);
    aGameState->AddSprite(mSprite);
    mSprite->x = BOARD_X + aCol * 16;
    mSprite->y = BOARD_Y + aRow * 16;
    mSprite->flags |= SFLAG_RENDER;
    mSprite->StartAnimation(BombDropAnimation);
    gSoundPlayer.PlaySound(/*SFX_GOOD_DROP_BLOCK_WAV*/0, 0, EFalse);
  }
  ~EmptyExplosion() {
    mSprite->Remove();
    delete mSprite;
  }

  TBool RunBefore() {
    return ETrue;
  }
  TBool RunAfter() {
    if (mSprite->AnimDone()) {
      return EFalse;
    }
    return ETrue;
  }
protected:
  BAnimSprite *mSprite;
};
void GModusBombPowerup::ExplodeBlock(TInt aRow, TInt aCol) {
  if (mGameBoard->IsEmpty(aRow, aCol)) {
    mGameState->AddProcess(new EmptyExplosion(aRow, aCol, mGameState));
  }
  else {
    mGameBoard->ExplodeBlock(aRow, aCol);
  }
}

TBool GModusBombPowerup::StateRemove() {
  if (mBombTimer--) {
    return ETrue;
  }
  mBombTimer = 30 / 4;        // 1/8 second

  TInt row = mBombRow,
       col = mBombCol;

  switch (mBombStep++) {
    case 0:
      ExplodeBlock(row, col);
      return ETrue;
    case 1:
      ExplodeBlock(row - 1, col - 1);
      ExplodeBlock(row - 1, col);
      ExplodeBlock(row - 1, col + 1);
      ExplodeBlock(row, col - 1);
      ExplodeBlock(row, col + 1);
      ExplodeBlock(row + 1, col - 1);
      ExplodeBlock(row + 1, col);
      ExplodeBlock(row + 1, col + 1);
      return ETrue;
    case 2:
      ExplodeBlock(row - 2, col);
      ExplodeBlock(row, col - 2);
      ExplodeBlock(row, col + 2);
      ExplodeBlock(row + 2, col);
      return ETrue;
    default:
      // done!
      mState = STATE_WAIT;
      return ETrue;
  }
}

TBool GModusBombPowerup::StateWait() {
  if (mPlayerSprite->AnimDone()) {
    mPlayerSprite->flags |= SFLAG_RENDER;
    gControls.dKeys = 0;  // in case user pressed a key during removing blocks
    mGameState->Next(EFalse);
    return EFalse;
  }
  return ETrue;
}

TBool GModusBombPowerup::RunAfter() {
  switch (mState) {
    case STATE_MOVE:
      return StateMove();
    case STATE_REMOVE:
      return StateRemove();
    case STATE_TIMER:
      return StateMove();
    case STATE_WAIT:
      return StateWait();
  }
  return ETrue;
}