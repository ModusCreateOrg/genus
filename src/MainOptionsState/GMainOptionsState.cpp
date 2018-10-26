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
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    else if (gControls.WasPressed(BUTTON_MENU)) {
      gGame->SetState(GAME_STATE_CREDITS);
      return EFalse;
    }
    return ETrue;
  }
};

class GMainOptionsPlayfield : public BPlayfield {
public:
  GMainOptionsPlayfield() {
    gResourceManager.LoadBitmap(MAIN_OPTIONS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }
  virtual ~GMainOptionsPlayfield() {

  }
public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }
public:
  BBitmap *mBackground;
};


GMainOptionsState::GMainOptionsState() : BGameEngine(gViewPort) {
  mPlayfield = new GMainOptionsPlayfield();
  auto *p = new GMainOptionsProcess();
  AddProcess(p);
  gSoundPlayer.PlayMusic(SONG0_XM);
}

GMainOptionsState::~GMainOptionsState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}


