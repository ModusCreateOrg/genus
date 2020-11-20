#include "GModusBombPowerup.h"
//#include "GGameState.h"
#include "Game.h"
static const TUint16 ANIM_SPEED = 2;
static ANIMSCRIPT BombAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP(ANIM_SPEED, IMG_POWERUP_MODUS_BOMB),
  ASTEP(ANIM_SPEED, IMG_POWERUP_MODUS_BOMB + 1),
  ALOOP
};

static ANIMSCRIPT BombDropAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ASTEP(ANIM_SPEED, IMG_POWERUP_MODUS_BOMB + 2),
  ASTEP(ANIM_SPEED, IMG_POWERUP_MODUS_BOMB + 3),
  ASTEP(ANIM_SPEED, IMG_POWERUP_MODUS_BOMB + 4),
  ASTEP(ANIM_SPEED, IMG_POWERUP_MODUS_BOMB + 5),
  ASTEP(ANIM_SPEED, IMG_POWERUP_MODUS_BOMB + 6),
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
  if (gControls.WasPressed(BUTTONB)) {
    if (mGameState->MainState() != STATE_REMOVE) {
      Drop();
      mState = STATE_REMOVE;
      mGameState->MainState(STATE_WAIT);
      mPlayerSprite->StartAnimation(BombDropAnimation);
    } else {
      gSoundPlayer.SfxBadDrop();
    }
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
    gSoundPlayer.SfxExplodeBlock();
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
  if (aRow < 0 || aRow >= BOARD_ROWS) {
    return;
  }
  if (aCol < 0 || aCol >= BOARD_COLS) {
    return;
  }
  if (mGameBoard->IsEmpty(aRow, aCol)) {
    mGameState->AddProcess(new EmptyExplosion(aRow, aCol, mGameState));
  }
  else {
    mGameBoard->ExplodeBlock(aRow, aCol);
  }
  gControls.Rumble(0.1, 100);
}

TBool GModusBombPowerup::StateRemove() {
  if (mBombTimer--) {
    return ETrue;
  }

  mBombTimer = 30 / 3;        // 1/8 second
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
