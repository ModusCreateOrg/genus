#include "GNoPowerup.h"
#include "Game.h"

static const TInt BLINK_TIME = 2;

GNoPowerup::GNoPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : BPowerup(aSprite, aGameState) {
  mPlayerSprite->mBlockSize = BLOCKSIZE_2x2;
  mState      = STATE_MOVE;
  mBlinkTimer = BLINK_TIME;
}

GNoPowerup::~GNoPowerup() {

}

void GNoPowerup::Wait() {
  mState = STATE_WAIT;
}

void GNoPowerup::Signal() {
  if (mGameBoard->Combine()) {
    mGameState->StartBonusTimer();
    mState = STATE_TIMER;
  } else if (mGameState->mBonusTimer >= 0) {
    mState = STATE_TIMER;
  } else {
    mState = STATE_MOVE;
  }
}

TBool GNoPowerup::CanDrop() {
  TInt row = mPlayerSprite->BoardRow(),
       col = mPlayerSprite->BoardCol();

  if (mGameBoard->mBoard[row][col] != 255 || mGameBoard->mBoard[row][col + 1] != 255 ||
      mGameBoard->mBoard[row + 1][col] != 255 || mGameBoard->mBoard[row + 1][col + 1] != 255) {
    return EFalse;
  }
  return ETrue;
}


TBool GNoPowerup::Drop() {
  const TInt   row = mPlayerSprite->BoardRow(),
               col = mPlayerSprite->BoardCol();
  const TUint8 *b  = mPlayerSprite->mBlocks;

  TUint8 (*p)[BOARD_ROWS][BOARD_COLS] = &mGameBoard->mBoard;
  (*p)[row][col]         = b[0];
  (*p)[row][col + 1]     = b[1];
  (*p)[row + 1][col]     = b[2];
  (*p)[row + 1][col + 1] = b[3];

  TBool ret = mGameBoard->Combine();
  // Get Next 2x2 into current, maybe powerup
  mGameState->Next(mState == STATE_MOVE && !ret);
  return ret;
}

void GNoPowerup::Blink() {
  if (mGameState->mGameOver) {
    return;
  }
  TBool canDrop = CanDrop();
  mBlinkTimer--;
  if (mBlinkTimer < 0) {
    mBlinkTimer = BLINK_TIME;
    if (!canDrop) {
      mPlayerSprite->flags ^= SFLAG_RENDER;
    }
  } else if (canDrop) {
    mPlayerSprite->flags |= SFLAG_RENDER;
  }
}

TBool GNoPowerup::MoveState() {
  mRepeatTimer--;

  if (mGameBoard->IsGameOver()) {
    mGameState->GameOver();
    mState = STATE_WAIT;
    mPlayerSprite->flags &= SFLAG_RENDER | SFLAG_ANIMATE;
    return ETrue;
  }

  if (gControls.WasPressed(BUTTONA)) {
    RotateRight();
//  } else if (gControls.WasPressed(BUTTONB)) {
//    RotateLeft();
  }else if (TimedControl(JOYLEFT)) {
    MoveLeft();
  } else if (TimedControl(JOYRIGHT)) {
    MoveRight();
  } else if (TimedControl(JOYUP)) {
    MoveUp();
  } else if (TimedControl(JOYDOWN)) {
    MoveDown();
  }

  if (gControls.WasPressed(BUTTONB)) {
    if (CanDrop()) {
      if (Drop()) {
        // combined!
        // start bonus timer, if not already started
        gSoundPlayer.SfxCombo();
        mGameState->StartBonusTimer();
        mState = STATE_TIMER;
        return ETrue;
      } else {
        gSoundPlayer.SfxGoodDrop();
      }
    } else {
      // can't drop sound:
      gSoundPlayer.SfxBadDrop();
    }
  }
  Blink();
  return ETrue;
}

TBool GNoPowerup::TimerState() {
  if (mGameBoard->IsGameOver()) {
    mGameState->mBonusTimer = 0;
  }
  if (mGameState->mBonusTimer >= 0) {
    mGameState->mBonusTimer--;
    if (mGameState->mBonusTimer < 0) {
      mRemoveRow   = mRemoveCol = 0;
      mRemoveScore = 1;
      mRemoveTimer = 1;
      mPlayerSprite->flags &= ~SFLAG_RENDER;
      mState = STATE_REMOVE;
      return ETrue;
    }
  }
  mRepeatTimer--;

  if (gControls.WasPressed(BUTTONA)) {
    RotateRight();
//  } else if (gControls.WasPressed(BUTTONB)) {
//    RotateRight();
  } else if (TimedControl(JOYLEFT)) {
    MoveLeft();
  } else if (TimedControl(JOYRIGHT)) {
    MoveRight();
  } else if (TimedControl(JOYUP)) {
    MoveUp();
  } else if (TimedControl(JOYDOWN)) {
    MoveDown();
  }

  if (gControls.WasPressed(BUTTONB)) {
    if (CanDrop()) {
      gSoundPlayer.SfxGoodDrop();
      Drop();
    } else {
      // can't drop sound:
      gSoundPlayer.SfxBadDrop();
    }
  }

  Blink();
  return ETrue;
}

TBool GNoPowerup::RemoveState() {
  if (mRemoveTimer > 0) {
    if (mRemoveTimer--) {
      return ETrue;
    }
  }
  mRemoveTimer = 30 / 8;        // 1/8 second

  while (mRemoveRow < BOARD_ROWS) {
    if (mRemoveCol >= BOARD_COLS) {
      mRemoveCol = 0;
      mRemoveRow++;
      if (mRemoveRow >= BOARD_ROWS) {
        // all done, game resumes
        gControls.dKeys = 0;  // in case user pressed a key during removing blocks
        if (mGameBoard->IsGameOver()) {
          mState = STATE_WAIT;
          mPlayerSprite->flags &= ~SFLAG_RENDER;
        }
        else {
          mPlayerSprite->flags |= SFLAG_RENDER;
          mState = STATE_MOVE;
        }
        return ETrue;
      }
    }
    TUint8 v = mGameBoard->mBoard[mRemoveRow][mRemoveCol];
    if (v != 255) {
      if ((v > 0 && v <= 5) || (v > 16 && v <= 21)) {
        TBCD add;
        add.FromUint32(mRemoveScore);
        mGameState->mScore.Add(add);
        mRemoveScore++;
        // remove the block - start explosion
        mGameBoard->ExplodeBlock(mRemoveRow, mRemoveCol);
        if (mGameState->mBlocksRemaining > 0) {
          mGameState->mBlocksRemaining--;
        }

        mRemoveCol++;
        return ETrue;
      }
    }
    mRemoveCol++;
  }
  gControls.dKeys = 0;  // in case user pressed a key during removing blocks
  if (mGameBoard->IsGameOver()) {
    mState = STATE_WAIT;
    mPlayerSprite->flags &= ~SFLAG_RENDER;
  }
  else {
    mPlayerSprite->flags |= SFLAG_RENDER;
    mState = STATE_MOVE;
  }
  return ETrue;
}

TBool GNoPowerup::WaitState() {
  return ETrue;
}

TBool GNoPowerup::RunBefore() {
  if (mGameState->mGameOver) {
    mPlayerSprite->flags &= ~SFLAG_RENDER;
  }
  return ETrue;
}

TBool GNoPowerup::RunAfter() {
  if (mGameState->mGameOver) {
    return ETrue;
  }
  switch (mState) {
    case STATE_MOVE:
      return MoveState();
    case STATE_TIMER:
      return TimerState();
    case STATE_REMOVE:
      return RemoveState();
    case STATE_WAIT:
      return WaitState();
  }
  return ETrue;
}
