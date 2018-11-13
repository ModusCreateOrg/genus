#include "GModusBombPowerup.h"
#include "GGameState.h"
#include "Game.h"

static ANIMSCRIPT BombAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP1(IMG_POWERUP_MODUS),
  ASTEP1(IMG_POWERUP_MODUS + 1),
  ALOOP
};

GModusBombPowerup::GModusBombPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : BPowerup(aSprite, aGameState) {
  mSprite->mBlockSize = BLOCKSIZE_1x1;
  mSprite->StartAnimation(BombAnimation);
  mState = STATE_MOVE;
}

GModusBombPowerup::~GModusBombPowerup() {

}

TBool GModusBombPowerup::Drop() {
  // disable rendering
  mSprite->flags &= ~SFLAG_RENDER;

  // where on the board the bomb was placed
  mBombRow = mSprite->BoardRow();
  mBombCol = mSprite->BoardCol();

  mBombStep  = 0;  // animation step
  mBombTimer = 1; // 1st step immediately
  mDropped   = ETrue;

  return EFalse;
}

TBool GModusBombPowerup::StateMove() {
  mRepeatTimer--;

  if (gControls.WasPressed(BUTTONA)) {
    RotateLeft();
  } else if (gControls.WasPressed(BUTTONB)) {
    RotateRight();
  } else if (TimedControl(JOYLEFT)) {
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
  }

  return ETrue;
}

TBool GModusBombPowerup::StateRemove() {
  if (mBombTimer--) {
    return ETrue;
  }
  mBombTimer = 30 / 2;        // 1/8 second

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
    case 3:
      mGameBoard->ExplodeBlock(row - 2, col);
      mGameBoard->ExplodeBlock(row, col - 2);
      mGameBoard->ExplodeBlock(row, col + 2);
      mGameBoard->ExplodeBlock(row + 2, col);
      return ETrue;
    default:
      // done!
      mSprite->flags |= SFLAG_RENDER;
      gControls.dKeys             = 0;  // in case user pressed a key during removing blocks
      mGameState->Next(EFalse);
      return EFalse;
  }
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
        return ETrue;
  }
  return ETrue;
}