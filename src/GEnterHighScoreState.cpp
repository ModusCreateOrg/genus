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
      gGame->SetState(GAME_STATE_HIGH_SCORES);
      return EFalse;
    }
    return ETrue;
  }
};

class GEnterHighScorePlayfield : public BPlayfield {
public:
  GEnterHighScorePlayfield() {
    gResourceManager.LoadBitmap(ENTER_INITIALS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }
  ~GEnterHighScorePlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }
public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }

public:
  BBitmap *mBackground;
};

GEnterHighScoreState::GEnterHighScoreState() : BGameEngine(gViewPort) {
  mPlayfield = new GEnterHighScorePlayfield();
  auto *p = new GEnterHighScoreProcess();
  AddProcess(p);
}

GEnterHighScoreState::~GEnterHighScoreState() {
  // delete mPlayfield;
}

