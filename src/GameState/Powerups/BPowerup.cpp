#include "BPowerup.h"
#include "GGameState.h"
#include "GGameBoard.h"
#include "GGame.h"

static const TInt REPEAT_TIME  = 1,
                  REPEAT_DELAY = REPEAT_TIME + 2;

TInt BPowerup::mRepeatTimer = 0;

BPowerup::BPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : mSprite(aSprite), mGameState(aGameState) {
  mGameBoard = &mGameState->mGameBoard;
  mDropped = EFalse;
  mSprite->mBlockSize = BLOCKSIZE_2x2;
  mSprite->flags |= SFLAG_RENDER;
}

BPowerup::~BPowerup() {

}

// slow down repeat button press
TBool BPowerup::TimedControl(TUint16 aButton) {
  if (gControls.WasPressed(aButton)) {
    return ETrue;
  } else if (mRepeatTimer < 1) {
    return gControls.IsPressed(aButton);
  }
  return EFalse;
}

TBool BPowerup::Move() {
  // TODO: remove this for production
  if (gControls.WasPressed(BUTTON_START)) {
    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }

  mRepeatTimer--;

  if (gControls.WasPressed(BUTTONA)) {
    mSprite->RotateLeft();
    mRepeatTimer = REPEAT_DELAY;
  } else if (gControls.WasPressed(BUTTONB)) {
    mSprite->RotateRight();
    mRepeatTimer = REPEAT_DELAY;
  } else if (TimedControl(JOYLEFT)) {
    mSprite->x -= 16;
    if (mSprite->x < PLAYER_X_MIN) {
      mSprite->x = PLAYER_X_MIN;
    }
    mRepeatTimer = REPEAT_DELAY;
  } else if (TimedControl(JOYRIGHT)) {
    mSprite->x += 16;
    if (mSprite->mBlockSize == BLOCKSIZE_1x1) {
      if (mSprite->x > (PLAYER_X_MAX + 16)) {
        mSprite->x = PLAYER_X_MAX + 16;
      }
    } else {
      if (mSprite->x > PLAYER_X_MAX) {
        mSprite->x = PLAYER_X_MAX;
      }
    }
    mRepeatTimer = REPEAT_DELAY;
  } else if (TimedControl(JOYUP)) {
    mSprite->y -= 16;
    if (mSprite->y < PLAYER_Y_MIN) {
      mSprite->y = PLAYER_Y_MIN;
    }
    mRepeatTimer = REPEAT_DELAY;
  } else if (TimedControl(JOYDOWN)) {
    mSprite->y += 16;
    if (mSprite->mBlockSize == BLOCKSIZE_1x1) {
      if (mSprite->y > (PLAYER_Y_MAX + 16)) {
        mSprite->y = PLAYER_Y_MAX + 16;
      }
    } else {
      if (mSprite->y > PLAYER_Y_MAX) {
        mSprite->y = PLAYER_Y_MAX;
      }
    }
    mRepeatTimer = REPEAT_DELAY;
  }
  return ETrue;
}
