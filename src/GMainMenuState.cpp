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
      gGame->SetState(GAME_STATE_GAME);
      return EFalse;
    }
    else if (gControls.WasPressed(BUTTON_MENU)) {
      gGame->SetState(GAME_STATE_MAIN_OPTIONS);
      return EFalse;
    }
    return ETrue;
  }
};

class GMainMenuPlayfield : public BPlayfield {
public:
  GMainMenuPlayfield() {
    gResourceManager.LoadBitmap(MAIN_MENU1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }
  virtual ~GMainMenuPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }

public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }

public:
  BBitmap *mBackground;

};

GMainMenuState::GMainMenuState() : BGameEngine(gViewPort) {
  mPlayfield = new GMainMenuPlayfield();
  auto *p = new GMainMenuProcess();
  AddProcess(p);
}

GMainMenuState::~GMainMenuState() {
  // delete mPlayfield
}

