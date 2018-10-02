#include "Game.h"

class GMainMenuProcess : public BProcess {
public:
  GMainMenuProcess() : BProcess() {}

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_START)) {
      gGameEngine->SetState(GAME_STATE_GAME);
      return EFalse;
    }
    return ETrue;
  }
};

GMainMenuState::GMainMenuState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(MAIN_MENU1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  auto *p = new GMainMenuProcess();
  aGameEngine->AddProcess(p);
}

GMainMenuState::~GMainMenuState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GMainMenuState::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}
