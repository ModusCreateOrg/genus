#include "GModusBombPowerup.h"
//#include "GGameState.h"
#include "Game.h"

static ANIMSCRIPT BombAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP1(IMG_POWERUP_MODUS),
  ASTEP1(IMG_POWERUP_MODUS + 1),
  ALOOP
};

static ANIMSCRIPT BombDropAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ASTEP1(IMG_POWERUP_MODUS + 2),
  ASTEP1(IMG_POWERUP_MODUS + 3),
  ASTEP1(IMG_POWERUP_MODUS + 4),
  ASTEP1(IMG_POWERUP_MODUS + 5),
  ASTEP1(IMG_POWERUP_MODUS + 6),
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

TBool GModusBombPowerup::StateRemove() {
  if (mBombTimer--) {
    return ETrue;
  }
  mBombTimer = 30 / 4;        // 1/8 second

  TInt row = mBombRow,
       col = mBombCol;

  switch (mBombStep++) {
    case 0:
      mGameBoard->ExplodeBlock(row, col);
      return ETrue;
    case 1:
      mGameBoard->ExplodeBlock(row - 1, col - 1);
      mGameBoard->ExplodeBlock(row - 1, col);
      mGameBoard->ExplodeBlock(row - 1, col + 1);
      mGameBoard->ExplodeBlock(row, col - 1);
      mGameBoard->ExplodeBlock(row, col + 1);
      mGameBoard->ExplodeBlock(row + 1, col - 1);
      mGameBoard->ExplodeBlock(row + 1, col);
      mGameBoard->ExplodeBlock(row + 1, col + 1);
      return ETrue;
    case 2:
      mGameBoard->ExplodeBlock(row - 2, col);
      mGameBoard->ExplodeBlock(row, col - 2);
      mGameBoard->ExplodeBlock(row, col + 2);
      mGameBoard->ExplodeBlock(row + 2, col);
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