#include "Game.h"

class GSplashProcess : public BProcess {
public:
  GSplashProcess() : BProcess() {
    mTimer = 30*6;
  }

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_ANY) || --mTimer <= 0) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }
  TInt mTimer;
};

class GSplashPlayfield : public BPlayfield {
public:
  GSplashPlayfield() {
    gResourceManager.LoadBitmap(SPLASH1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }

  virtual ~GSplashPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }

  void Render() {
    gSoundPlayer.PlayMusic(SONG0_XM);
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }
public:
  BBitmap *mBackground;
};

GSplashState::GSplashState() : BGameEngine(gViewPort) {
  mPlayfield = new GSplashPlayfield();
  auto *p = new GSplashProcess();
  AddProcess(p);
}

GSplashState::~GSplashState() {
//  delete mPlayfield;
}

