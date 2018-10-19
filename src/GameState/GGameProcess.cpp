#include "Game.h"
#include "GGameProcess.h"

static const TInt BLINK_TIME = 2;

static const TInt PLAYERSTATE_CONTROL  = 0,
                  PLAYERSTATE_GAMEOVER = 1;

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

  if (mGameBoard->mGameBoard[row][col] != 255 || mGameBoard->mGameBoard[row][col + 1] != 255 ||
      mGameBoard->mGameBoard[row + 1][col] != 255 || mGameBoard->mGameBoard[row + 1][col + 1] != 255) {
    return EFalse;
  }
  return ETrue;
}

// returns ETrue if drop added to or created at least one 2x2 same blocks
TBool GGameProcess::Drop() {
  const TInt   row = BoardRow(),
               col = BoardCol();
  const TUint8 *b  = mSprite->mBlocks;

  TUint8 (*p)[BOARD_ROWS][BOARD_COLS] = &mGameBoard->mGameBoard;
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

void GGameProcess::StateControl() {
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
        printf("Drop true\n");
        TUint32 score = mGameBoard->CountScore();
        // move this logic to GGameState...

        if (score > 0) {
          gSoundPlayer.PlaySound(5,0,EFalse);
        }

        TBCD p;
        mGameState->mScore.Add(p);
      }
      gSoundPlayer.PlaySound(/*SFX_GOOD_DROP_BLOCK_WAV*/0, 0, EFalse);
      if (mGameBoard->IsGameOver()) {
        mState = PLAYERSTATE_GAMEOVER;
        mGameState->mGameOver = ETrue;
      }
    } else {
      // TODO: Jay - make a "cant do that!" sound here
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
}

TBool GGameProcess::RunAfter() {
  switch (mState) {
    case PLAYERSTATE_CONTROL:
      StateControl();
      break;
    case PLAYERSTATE_GAMEOVER:
      return StateGameOver();
    default:
      Panic("Invalid mState in RunAfter\n");
      break;
  }
  return ETrue;
}

