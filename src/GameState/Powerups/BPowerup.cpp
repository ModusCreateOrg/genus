#include "BPowerup.h"
#include "GGameState.h"
#include "GGameBoard.h"
#include "GGame.h"


TInt BPowerup::mRepeatTimer = 0;

BPowerup::BPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : mPlayerSprite(aSprite), mGameState(aGameState) {
  mGameBoard = &mGameState->mGameBoard;
  mPlayerSprite->mBlockSize = BLOCKSIZE_2x2;
//  mPlayerSprite->flags |= SFLAG_RENDER;
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

void BPowerup::MoveLeft() {
  mPlayerSprite->x -= 16;
  if (mPlayerSprite->x < PLAYER_X_MIN) {
    mPlayerSprite->x = PLAYER_X_MIN;
  }
  mRepeatTimer = REPEAT_DELAY;
}

void BPowerup::MoveRight() {
  mPlayerSprite->x += 16;
  if (mPlayerSprite->mBlockSize == BLOCKSIZE_1x1) {
    if (mPlayerSprite->x > (PLAYER_X_MAX + 16)) {
      mPlayerSprite->x = PLAYER_X_MAX + 16;
    }
  } else {
    if (mPlayerSprite->x > PLAYER_X_MAX) {
      mPlayerSprite->x = PLAYER_X_MAX;
    }
  }
  mRepeatTimer = REPEAT_DELAY;
}

void BPowerup::MoveUp() {
  mPlayerSprite->y -= 16;
  if (mPlayerSprite->y < PLAYER_Y_MIN) {
    mPlayerSprite->y = PLAYER_Y_MIN;
  }
  mRepeatTimer = REPEAT_DELAY;
}

void BPowerup::MoveDown() {
  mPlayerSprite->y += 16;
  if (mPlayerSprite->mBlockSize == BLOCKSIZE_1x1) {
    if (mPlayerSprite->y > (PLAYER_Y_MAX + 16)) {
      mPlayerSprite->y = PLAYER_Y_MAX + 16;
    }
  } else {
    if (mPlayerSprite->y > PLAYER_Y_MAX) {
      mPlayerSprite->y = PLAYER_Y_MAX;
    }
  }
  mRepeatTimer = REPEAT_DELAY;
}

void BPowerup::RotateLeft() {
  if (mPlayerSprite->mBlockSize == BLOCKSIZE_1x1) {
    //
  }
  else {
    mPlayerSprite->RotateLeft();
  }
}

void BPowerup::RotateRight() {
  if (mPlayerSprite->mBlockSize == BLOCKSIZE_1x1) {
    //
  }
  else {
    mPlayerSprite->RotateRight();
  }
}

