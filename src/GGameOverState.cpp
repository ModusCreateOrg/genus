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
      gGame->SetState(GAME_STATE_ENTER_HIGHSCORE);
      return EFalse;
    }
    return ETrue;
  }
};

class GGameOverPlayfield : public BPlayfield {
public:
  GGameOverPlayfield() {
    gResourceManager.LoadBitmap(GAME_OVER1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }

  virtual ~GGameOverPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }

public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }

public:
  BBitmap *mBackground;
};

GGameOverState::GGameOverState() : BGameEngine(gViewPort) {
  mPlayfield = new GGameOverPlayfield();
  auto *p = new GGameOverProcess();
  AddProcess(p);
}

GGameOverState::~GGameOverState() {
//  delete mPlayfield;
}


