#include "Game.h"
#include "GGameProcess.h"

#include "Powerups/Powerups.h"

static const TInt BLINK_TIME = 2;

enum {
  PLAYERSTATE_PLAY,
  PLAYERSTATE_REMOVE_BLOCKS,
  PLAYERSTATE_M_BOMB,
  PLAYERSTATE_GAME_OVER
};

static const TInt REPEAT_TIME  = 1,
                  REPEAT_DELAY = REPEAT_TIME + 2;

GGameProcess::GGameProcess(GGameState *aGameState) : BProcess() {
  mGameState  = aGameState;
  mGameBoard  = &mGameState->mGameBoard;
  mState      = PLAYERSTATE_PLAY;
  mBlinkTimer = BLINK_TIME;

  mSprite = new GPlayerSprite();
  aGameState->AddSprite(mSprite);
  mSprite->x  = PLAYER_X;
  mSprite->y  = PLAYER_Y;
  mSprite->vy = 0;

  mNextSprite    = new GPlayerSprite();
  aGameState->AddSprite(mNextSprite);
  mNextSprite->flags |= SFLAG_RENDER;
  mNextSprite->x = NEXT_BLOCK_X;
  mNextSprite->y = NEXT_BLOCK_Y;
  mNextSprite->Randomize();

  mPowerup = new GNoPowerup(mSprite, mGameState);
}

GGameProcess::~GGameProcess() {
  // sprites are automatically removed and deleted by BGameEngine
}

TBool GGameProcess::RunBefore() {
  if (mGameState->mBonusTime > 500) {
    printf("bad bonus time: %d\n", mGameState->mBonusTime);
  }
  return ETrue;
}

#if 0
/********************************************************************************************************************
 ********************************************************************************************************************
 ********************************************************************************************************************
 ** ____
 ** |  _ \ _ __ ___  _ __
 ** | | | | '__/ _ \| '_ \
 ** | |_| | | | (_) | |_) |
 ** |____/|_|  \___/| .__/
 **                 |_|
 ********************************************************************************************************************
 ********************************************************************************************************************
 *******************************************************************************************************************/
//
TBool GGameProcess::CanDrop() {
  if (mSprite->mPowerupType != POWERUP_TYPE_NONE) {
    // powerups can always be dropped
    return ETrue;
  }
  TInt row = mSprite->BoardRow(),
       col = mSprite->BoardCol();

  if (mGameBoard->mBoard[row][col] != 255 || mGameBoard->mBoard[row][col + 1] != 255 ||
      mGameBoard->mBoard[row + 1][col] != 255 || mGameBoard->mBoard[row + 1][col + 1] != 255) {
    return EFalse;
  }
  return ETrue;
}

// drop a 2x2 tile/block
void GGameProcess::Drop2x2() {
  const TInt   row = mSprite->BoardRow(),
               col = mSprite->BoardCol();
  const TUint8 *b  = mSprite->mBlocks;

  TUint8 (*p)[BOARD_ROWS][BOARD_COLS] = &mGameBoard->mBoard;
  (*p)[row][col]         = b[0];
  (*p)[row][col + 1]     = b[1];
  (*p)[row + 1][col]     = b[2];
  (*p)[row + 1][col + 1] = b[3];
}

// drop the M Bomb
void GGameProcess::DropMBomb() {
  mBombStep                   = 0;
  mState                      = PLAYERSTATE_M_BOMB;
  mSprite->flags &= ~SFLAG_RENDER;
  mGameState->mBlocksRemoving = ETrue;
  mRemoveTimer = 1;
  mRemoveRow   = mSprite->BoardRow();
  mRemoveCol   = mSprite->BoardCol();
}

// returns ETrue if drop added to or created at least one 2x2 same blocks
TBool GGameProcess::Drop() {
  switch (mSprite->mPowerupType) {
    case POWERUP_TYPE_NONE:
      Drop2x2();
      break;
    case POWERUP_TYPE_M_BOMB:
      DropMBomb();
      break;
  }
  mSprite->Copy(mNextSprite);
  mSprite->x = PLAYER_X;
  mSprite->y = PLAYER_Y;
  mNextSprite->Randomize();

  TBool ret = mGameBoard->Combine();
  if (!ret && mGameState->mBonusTimer < 0) {
    printf("bonus timer: %d\n", mGameState->mBonusTimer);
    mSprite->MaybePowerup();
  }
  return ret;
}
#endif

/********************************************************************************************************************
 ********************************************************************************************************************
 ********************************************************************************************************************
 **   ____  _        _
 **  / ___|| |_ __ _| |_ ___  ___
 **  \___ \| __/ _` | __/ _ \/ __|
 **  ___) | || (_| | ||  __/\__ \
 **  |____/ \__\__,_|\__\___||___/
 **
 ********************************************************************************************************************
 ********************************************************************************************************************
 ********************************************************************************************************************/

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


void GGameProcess::MaybePowerup() {
  TInt maybe = Random(15, 20);
  printf("maybe %d\n", maybe);
  delete mPowerup;
  if (maybe == 16) {
    mPowerup = new GModusBombPowerup(mSprite, mGameState);
  }
  else {
    mPowerup = new GNoPowerup(mSprite, mGameState);
  }
}

TBool GGameProcess::StatePlay() {
  // TODO: remove this for production
  if (gControls.WasPressed(BUTTON_START)) {
    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }
  mPowerup->Move();
  mPowerup->Run();
  if (gControls.WasPressed(BUTTON_SELECT)) {
    if (mPowerup->CanDrop()) {
      if (mPowerup->Drop(this)) {
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
        mSprite->Copy(mNextSprite);
        mSprite->x = PLAYER_X;
        mSprite->y = PLAYER_Y;
        mNextSprite->Randomize();
        MaybePowerup();
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
    if (!mPowerup->CanDrop()) {
      mSprite->flags ^= SFLAG_RENDER;
    }
  } else if (mPowerup->CanDrop()) {
    mSprite->flags |= SFLAG_RENDER;
  }
  // TODO: Game Over while removing blocks
  if (mGameBoard->IsGameOver() && mGameState->mBonusTimer < 0) {
    mState = PLAYERSTATE_GAME_OVER;
    mGameState->mGameOver = ETrue;
  }
  return ETrue;
}

#if 0
TBool GGameProcess::StateRemoveBlocks() {
  if (mRemoveTimer--) {
    return ETrue;
  }
  mRemoveTimer = 30 / 8;        // 1/8 second

  while (mRemoveRow < BOARD_ROWS) {
    if (mRemoveCol >= BOARD_COLS) {
      mRemoveCol = 0;
      mRemoveRow++;
      if (mRemoveRow >= BOARD_ROWS) {
        // all done, game resumes
        mState = PLAYERSTATE_PLAY;
        mGameState->mBlocksRemoving = EFalse;
        mSprite->flags |= SFLAG_RENDER;
        gControls.dKeys             = 0;  // in case user pressed a key during removing blocks
        break;
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
        break;
      }
    }
    mRemoveCol++;
  }
  return ETrue;
}

TBool GGameProcess::StateMBomb() {
  if (mRemoveTimer--) {
    return ETrue;
  }
  mRemoveTimer = 30 / 2;        // 1/8 second

  TInt row = mRemoveRow,
       col = mRemoveCol;

  switch (mBombStep++) {
    case 0:
      mGameBoard->ExplodeBlock(row, col);
      break;
    case 1:
      mGameBoard->ExplodeBlock(row - 1, col - 1);
      mGameBoard->ExplodeBlock(row - 1, col);
      mGameBoard->ExplodeBlock(row - 1, col + 1);
      mGameBoard->ExplodeBlock(row, col - 1);
      mGameBoard->ExplodeBlock(row, col + 1);
      mGameBoard->ExplodeBlock(row + 1, col - 1);
      mGameBoard->ExplodeBlock(row + 1, col);
      mGameBoard->ExplodeBlock(row + 1, col + 1);
      break;
    case 3:
      mGameBoard->ExplodeBlock(row - 2, col);
      mGameBoard->ExplodeBlock(row, col - 2);
      mGameBoard->ExplodeBlock(row, col + 2);
      mGameBoard->ExplodeBlock(row + 2, col);
      break;
    default:
      // done!
      mSprite->flags |= SFLAG_RENDER;
      mState = PLAYERSTATE_PLAY;
      gControls.dKeys             = 0;  // in case user pressed a key during removing blocks
      mGameState->mBlocksRemoving = EFalse;
      break;
  }
  return ETrue;
}
#endif

//void GGameProcess::RemoveBlocks() {
//  mState                      = PLAYERSTATE_REMOVE_BLOCKS;
//  mRemoveRow                  = mRemoveCol = 0;
//  mRemoveScore                = 1;
//  mRemoveTimer                = 1;
//  mSprite->flags &= ~SFLAG_RENDER;
//  mGameState->mBlocksRemoving = ETrue;
//}
TBool GGameProcess::RunAfter() {
  switch (mState) {
    case PLAYERSTATE_PLAY:
      return StatePlay();
//    case PLAYERSTATE_REMOVE_BLOCKS:
//      return StateRemoveBlocks();
    case PLAYERSTATE_GAME_OVER:
      return StateGameOver();
//    case PLAYERSTATE_M_BOMB:
//      return StateMBomb();
    default:
      Panic("Invalid mState in RunAfter\n");
  }
  return ETrue;
}

