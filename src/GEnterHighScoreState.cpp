#include "Game.h"

class GEnterHighScoreProcess : public BProcess {
public:
  GEnterHighScoreProcess() : BProcess() {}

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_START)) {
      gGameEngine->SetState(GAME_STATE_HIGH_SCORES);
      return EFalse;
    }
    return ETrue;
  }
};

GEnterHighScoreState::GEnterHighScoreState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(ENTER_INITIALS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  auto *p = new GEnterHighScoreProcess();
  aGameEngine->AddProcess(p);
}

GEnterHighScoreState::~GEnterHighScoreState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GEnterHighScoreState::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}

