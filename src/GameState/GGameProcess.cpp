#include "Game.h"
#include "GGameProcess.h"

#include "Powerups/Powerups.h"

#if 0
static const TInt BLINK_TIME = 2;

enum {
  PLAYERSTATE_PLAY,
  PLAYERSTATE_REMOVE_BLOCKS,
  PLAYERSTATE_M_BOMB,
  PLAYERSTATE_GAME_OVER
};

GGameProcess::GGameProcess(GGameState *aGameState) : BProcess() {
  mGameState  = aGameState;
  mGameBoard  = &mGameState->mGameBoard;
  mState      = PLAYERSTATE_PLAY;
  mBlinkTimer = BLINK_TIME;
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
//  if (mGameState->mBonusTimer < 0 && maybe == 16) {
//    if (Random() & 1) {
//      mPowerup = new GModusBombPowerup(mSprite, mGameState);
//    } else {
//      mPowerup = new GColorSwapPowerup(mSprite, mGameState);
//    }
//  } else {
    mPowerup = new GNoPowerup(mSprite, mGameState);
//  }
}

TBool GGameProcess::StatePlay() {
  // TODO: remove this for production
  if (gControls.WasPressed(BUTTON_START)) {
    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }
  mPowerup->Move();
  if (gControls.WasPressed(BUTTON_SELECT)) {
    if (mPowerup->CanDrop()) {
      gSoundPlayer.PlaySound(/*SFX_GOOD_DROP_BLOCK_WAV*/0, 0, EFalse);
      if (mPowerup->Drop(this)) {
        // combined!
        // start bonus timer, if not already started
        if (mGameState->mBonusTimer < 0) {
          mGameState->StartBonusTimer();
        }
      }
      mSprite->Copy(mNextSprite);
      mSprite->x = PLAYER_X;
      mSprite->y = PLAYER_Y;
      mNextSprite->Randomize();
      MaybePowerup();
    } else {
      // can't drop sound:
      gSoundPlayer.PlaySound(/*SFX_BAD_DROP_BLOCK_WAV*/1, 0, EFalse);
    }
  }

  if (!mPowerup->Run()) {
    TUint32 score = mGameBoard->CountScore();
    if (score > 0) {
      gSoundPlayer.PlaySound(5, 0, EFalse);
    }

    TBCD p;
    p.FromUint32(score);
    mGameState->mScore.Add(p);
  }
  if (!mGameState->mBlocksRemoving) {

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
      mGameState->
        mGameOver = ETrue;
    }
  }
  return ETrue;
}

TBool GGameProcess::RunAfter() {
  switch (mState) {
    case PLAYERSTATE_PLAY:
      return StatePlay();
    case PLAYERSTATE_GAME_OVER:
      return StateGameOver();
    default:
      Panic("Invalid mState in RunAfter\n");
  }
  return ETrue;
}
#endif
