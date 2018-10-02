#include "Game.h"

class GGameOverProcess : public BProcess {
public:
  GGameOverProcess() : BProcess() {}

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_START)) {
      gGameEngine->SetState(GAME_STATE_ENTER_HIGHSCORE);
      return EFalse;
    }
    return ETrue;
  }
};

GGameOverState::GGameOverState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(GAME_OVER1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  auto *p = new GGameOverProcess();
  aGameEngine->AddProcess(p);
}

GGameOverState::~GGameOverState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GGameOverState::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}

