#include "Game.h"

const TInt ANIMATE_TIME = 6;

class GGameProcess : public BProcess {
public:
  GGameProcess() : BProcess() {}

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_START)) {
      gGameEngine->SetState(GAME_STATE_GAMEOVER);
      return EFalse;
    }
    return ETrue;
  }
};

GGameState::GGameState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(LEVEL1_BKG1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(LEVEL1_BKG2_BMP, BKG2_SLOT, IMAGE_ENTIRE);
  mBackground1 = gResourceManager.GetBitmap(BKG_SLOT);
  mBackground2 = gResourceManager.GetBitmap(BKG2_SLOT);
  mCurrentBackground = mBackground1;
  gDisplay.SetPalette(mBackground1);
  mAnimationTimer = ANIMATE_TIME;

  auto *p = new GGameProcess();
  aGameEngine->AddProcess(p);
}

GGameState::~GGameState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
}

void GGameState::Animate() {
  if (--mAnimationTimer <= 0) {
    mCurrentBackground = mCurrentBackground == mBackground1 ? mBackground2 : mBackground1;
    mAnimationTimer = ANIMATE_TIME;
  }
}

void GGameState::Render() {
  gDisplay.renderBitmap->CopyPixels(mCurrentBackground);
}
