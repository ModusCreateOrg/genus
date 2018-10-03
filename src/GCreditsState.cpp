#include "Game.h"

class GCreditsProcess : public BProcess {
public:
  GCreditsProcess() : BProcess() {}

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_START)) {
      gGameEngine->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    else if (gControls.WasPressed(BUTTON_MENU)) {
      gGameEngine->SetState(GAME_STATE_MAIN_OPTIONS);
      return EFalse;
    }
    return ETrue;
  }
};

GCreditsState::GCreditsState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(CREDITS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  auto *p = new GCreditsProcess();
  aGameEngine->AddProcess(p);
}

GCreditsState::~GCreditsState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GCreditsState::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}


