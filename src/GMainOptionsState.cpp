#include "Game.h"

class GMainOptionsProcess : public BProcess {
public:
  GMainOptionsProcess() : BProcess() {}

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
      gGameEngine->SetState(GAME_STATE_CREDITS);
      return EFalse;
    }
    return ETrue;
  }
};

GMainOptionsState::GMainOptionsState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(MAIN_OPTIONS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  auto *p = new GMainOptionsProcess();
  aGameEngine->AddProcess(p);
}

GMainOptionsState::~GMainOptionsState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GMainOptionsState::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}

