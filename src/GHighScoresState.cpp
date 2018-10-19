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
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }
};

class GHighScoresPlayfield : public BPlayfield {
public:
  GHighScoresPlayfield() {
    gResourceManager.LoadBitmap(HIGH_SCORES1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }
  virtual ~GHighScoresPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }
public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }

public:
  BBitmap *mBackground;
};

GHighScoresState::GHighScoresState() : BGameEngine(gViewPort) {
  mPlayfield = new GHighScoresPlayfield();
  auto *p = new GHighScoresProcess();
  AddProcess(p);
}

GHighScoresState::~GHighScoresState() {
}

