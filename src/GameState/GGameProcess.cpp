#include "Game.h"
#include "GGameProcess.h"

static const TInt BLINK_TIME = 2;

enum {
  PLAYERSTATE_CONTROL,
  PLAYERSTATE_REMOVEBLOCKS,
  PLAYERSTATE_GAMEOVER
};

static const TInt REPEAT_TIME  = 1,
                  REPEAT_DELAY = REPEAT_TIME + 2;

GGameProcess::GGameProcess(GGameState *aGameState) : BProcess() {
  mGameState  = aGameState;
  mGameBoard  = &mGameState->mGameBoard;
  mState      = PLAYERSTATE_CONTROL;
  mBlinkTimer = BLINK_TIME;

  mSprite = new GPlayerSprite();
  aGameState->AddSprite(mSprite);
}

GGameProcess::~GGameProcess() {
}

TBool GGameProcess::RunBefore() {
  return ETrue;
}

TInt GGameProcess::BoardRow() {
  return mGameBoard->mBoardY + TInt(mSprite->y - BOARD_Y) / 16;

}

TInt GGameProcess::BoardCol() {
  return mGameBoard->mBoardX + TInt(mSprite->x - BOARD_X) / 16;
}

//
TBool GGameProcess::CanDrop() {
  TInt row = BoardRow(),
       col = BoardCol();

  if (mGameBoard->mBoard[row][col] != 255 || mGameBoard->mBoard[row][col + 1] != 255 ||
      mGameBoard->mBoard[row + 1][col] != 255 || mGameBoard->mBoard[row + 1][col + 1] != 255) {
    return EFalse;
  }
  return ETrue;
}

// returns ETrue if drop added to or created at least one 2x2 same blocks
TBool GGameProcess::Drop() {
  const TInt   row = BoardRow(),
               col = BoardCol();
  const TUint8 *b  = mSprite->mBlocks;

  TUint8 (*p)[BOARD_ROWS][BOARD_COLS] = &mGameBoard->mBoard;
  (*p)[row][col]         = b[0];
  (*p)[row][col + 1]     = b[1];
  (*p)[row + 1][col]     = b[2];
  (*p)[row + 1][col + 1] = b[3];

  mSprite->Randomize();

  return mGameBoard->Combine();
}

TBool GGameProcess::StateGameOver() {
  mSprite->mGameOver = ETrue;
  mSprite->flags &= ~SFLAG_RENDER;
  if (gControls.WasPressed(BUTTON_START)) {
    gGameEngine->RemoveSprite(mSprite);
    delete mSprite;
    mSprite = ENull;

    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }
  return ETrue;
}

// slow down repeat button press
TBool GGameProcess::TimedControl(TUint16 aButton) {
  if (gControls.WasPressed(aButton)) {
    mRepeatTimer = REPEAT_DELAY;
    return ETrue;
  } else if (mRepeatTimer < 1) {
    return gControls.IsPressed(aButton);
  }
  return EFalse;
}

TBool GGameProcess::StateControl() {
  if (gControls.WasPressed(BUTTON_START)) {
    gGameEngine->RemoveSprite(mSprite);
    delete mSprite;
    mSprite = ENull;

    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }
  mRepeatTimer--;
  if (gControls.WasPressed(BUTTONA)) {
    mSprite->RotateLeft();
  } else if (gControls.WasPressed(BUTTONB)) {
    mSprite->RotateRight();
  } else if (TimedControl(JOYLEFT)) {
    mSprite->x -= 16;
    if (mSprite->x < PLAYER_X_MIN) {
      mSprite->x          = PLAYER_X_MIN;
      mGameBoard->mBoardX = MAX(mGameBoard->mBoardX - 1, 0);
    }
  } else if (TimedControl(JOYRIGHT)) {
    mSprite->x += 16;
    if (mSprite->x > PLAYER_X_MAX) {
      mSprite->x          = PLAYER_X_MAX;
      mGameBoard->mBoardX = MIN(mGameBoard->mBoardX + 1, BOARD_X_MAX);
    }
  } else if (TimedControl(JOYUP)) {
    mSprite->y -= 16;
    if (mSprite->y < PLAYER_Y_MIN) {
      mSprite->y          = PLAYER_Y_MIN;
      mGameBoard->mBoardY = MAX(mGameBoard->mBoardY - 1, 0);
    }
  } else if (TimedControl(JOYDOWN)) {
    mSprite->y += 16;
    if (mSprite->y > PLAYER_Y_MAX) {
      mSprite->y          = PLAYER_Y_MAX;
      mGameBoard->mBoardY = MIN(mGameBoard->mBoardY + 1, BOARD_Y_MAX);
    }
  } else if (gControls.WasPressed(BUTTON_SELECT)) {
    if (CanDrop()) {
      if (Drop()) {
        // start bonus timer, if not already started
        if (mGameState->mBonusTimer < 0) {
          mGameState->StartBonusTimer();
          TUint32 score = mGameBoard->CountScore();
          if (score > 0) {
            gSoundPlayer.PlaySound(5, 0, EFalse);
          }

          TBCD p;
          p.FromUint32(score);
          mGameState->mScore.Add(p);
        }
      }
      gSoundPlayer.PlaySound(/*SFX_GOOD_DROP_BLOCK_WAV*/0, 0, EFalse);
    } else {
      // can't drop sound:
      gSoundPlayer.PlaySound(/*SFX_BAD_DROP_BLOCK_WAV*/1, 0, EFalse);
    }
  }
  if (mRepeatTimer < 1) {
    mRepeatTimer = 3;
  }
  mBlinkTimer--;
  if (mBlinkTimer < 0) {
    mBlinkTimer = BLINK_TIME;
    if (!CanDrop()) {
      mSprite->flags ^= SFLAG_RENDER;
    }
  } else if (CanDrop()) {
    mSprite->flags |= SFLAG_RENDER;
  }
  if (mGameBoard->IsGameOver()) {
    if (mGameState->mBonusTimer >= 0) {
      mGameState->mBonusTimer = -1;
    } else {
      mState = PLAYERSTATE_GAMEOVER;
      mGameState->mGameOver = ETrue;
    }
  }
  return ETrue;
}

TBool GGameProcess::StateRemoveBlocks() {
  if (mRemoveTimer--) {
    return ETrue;
  }
  mRemoveTimer = 30 / 4;        // 1/4 second

  while (mRemoveRow < BOARD_ROWS) {
    if (mRemoveCol >= BOARD_COLS) {
      mRemoveCol = 0;
      mRemoveRow++;
      if (mRemoveRow >= BOARD_ROWS) {
        // all done, game resumes
        mState = PLAYERSTATE_CONTROL;
        mSprite->flags |= SFLAG_RENDER;
        break;
      }
    }
    TUint8 v = mGameBoard->mBoard[mRemoveRow][mRemoveCol];
    if (v != 255) {
      if (mGameBoard->mBoard[mRemoveRow][mRemoveCol] & 8) {
        TBCD add;
        add.FromUint32(mRemoveScore);
        mGameState->mScore.Add(add);
        // TODO: Jay, add a sound here for the score incrementing as we remove blocks
        // sound lasts roughly 1/4 second
        mRemoveScore++;
        // remove the block
        mGameBoard->mBoard[mRemoveRow][mRemoveCol] = 255;
        mRemoveCol++;
        break;
      }
    }
    mRemoveCol++;
  }
  return ETrue;
}

void GGameProcess::RemoveBlocks() {
  mState       = PLAYERSTATE_REMOVEBLOCKS;
  mRemoveRow   = mRemoveCol = 0;
  mRemoveScore = 1;
  mRemoveTimer = 1;
  mSprite->flags &= ~SFLAG_RENDER;
}

TBool GGameProcess::RunAfter() {
  switch (mState) {
    case PLAYERSTATE_CONTROL:
      return StateControl();
    case PLAYERSTATE_REMOVEBLOCKS:
      return StateRemoveBlocks();
    case PLAYERSTATE_GAMEOVER:
      return StateGameOver();
    default:
      Panic("Invalid mState in RunAfter\n");
  }
  return ETrue;
}

