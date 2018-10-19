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
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    else if (gControls.WasPressed(BUTTON_MENU)) {
      gGame->SetState(GAME_STATE_MAIN_OPTIONS);
      return EFalse;
    }
    return ETrue;
  }
};

class GCreditsPlayfield : public BPlayfield {
public:
  GCreditsPlayfield() {
    gResourceManager.LoadBitmap(CREDITS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }

  virtual ~GCreditsPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }

public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }

public:
  BBitmap *mBackground;
};

GCreditsState::GCreditsState() : BGameEngine(gViewPort) {
  mPlayfield = new GCreditsPlayfield();
  auto *p = new GCreditsProcess();
  AddProcess(p);
}

GCreditsState::~GCreditsState() {
//  delete mPlayfield;
}


