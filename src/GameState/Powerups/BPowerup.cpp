#include "BPowerup.h"
#include "GGameState.h"
#include "GGameBoard.h"
#include "GGame.h"


TInt BPowerup::mRepeatTimer = 0;

BPowerup::BPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : mSprite(aSprite), mGameState(aGameState) {
  mGameBoard = &mGameState->mGameBoard;
  mDropped   = EFalse;
  mSprite->mBlockSize = BLOCKSIZE_2x2;
//  mSprite->flags |= SFLAG_RENDER;
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
  mSprite->x -= 16;
  if (mSprite->x < PLAYER_X_MIN) {
    mSprite->x = PLAYER_X_MIN;
  }
  mRepeatTimer = REPEAT_DELAY;
}

void BPowerup::MoveRight() {
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
}

void BPowerup::MoveUp() {
  mSprite->y -= 16;
  if (mSprite->y < PLAYER_Y_MIN) {
    mSprite->y = PLAYER_Y_MIN;
  }
  mRepeatTimer = REPEAT_DELAY;
}

void BPowerup::MoveDown() {
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

void BPowerup::RotateLeft() {
  if (mSprite->mBlockSize == BLOCKSIZE_1x1) {
    //
  }
  else {
    mSprite->RotateLeft();
  }
}

void BPowerup::RotateRight() {
  if (mSprite->mBlockSize == BLOCKSIZE_1x1) {
    //
  }
  else {
    mSprite->RotateRight();
  }
}

