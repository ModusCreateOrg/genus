#include "Game.h"

class GHighScoresProcess : public BProcess {
public:
  GHighScoresProcess() : BProcess() {}

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_START)) {
      gGameEngine->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }
};

GHighScoresState::GHighScoresState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(HIGH_SCORES1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  auto *p = new GHighScoresProcess();
  aGameEngine->AddProcess(p);
}

GHighScoresState::~GHighScoresState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GHighScoresState::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}

