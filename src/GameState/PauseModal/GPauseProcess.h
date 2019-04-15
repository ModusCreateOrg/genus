#ifndef GENUS_GPAUSEPROCESS_H
#define GENUS_GPAUSEPROCESS_H

#include "BProcess.h"
#include "GGameState.h"
#include "BPowerup.h"

class GPauseProcess : public BProcess {
  public:
    GPauseProcess(GGameState *aState) : BProcess() {
      mState = aState;
      mPrevMainState = mState->MainState();
    }

    ~GPauseProcess() {}

    TBool RunBefore() {
      const TBool powerupMoveState = !mState->mPowerup || (mState->mPowerup && mState->mPowerup->State() != STATE_REMOVE);

      if (gControls.WasPressed(BUTTON_START) && powerupMoveState) {
        if (mState->MainState() == STATE_WAIT) {
          // Resume
          mState->mSprite->flags |= (SFLAG_RENDER | SFLAG_ANIMATE);
          mState->mNextSprite->flags |= SFLAG_RENDER;

          mState->MainState(mPrevMainState);
          mState->mIsPaused = EFalse;
          gSoundPlayer.SfxMenuCancel();
        } else {
          // Pause
          mState->mSprite->flags &= ~(SFLAG_RENDER | SFLAG_ANIMATE);
          mState->mNextSprite->flags &= ~SFLAG_RENDER;

          mPrevMainState = mState->MainState();
          gOptions->gameProgress.gameState = mPrevMainState;
          mState->MainState(STATE_WAIT);
          mState->mIsPaused = ETrue;
        }
      }
      return ETrue;
    }

    TBool RunAfter() {
      return ETrue;
    }

    GGameState *mState;
    TPowerUpStates mPrevMainState;
};

#endif //GENUS_GPAUSEPROCESS_H
