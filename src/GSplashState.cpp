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
      gGameEngine->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }
  TInt mTimer;
};

GSplashState::GSplashState(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  gResourceManager.LoadBitmap(SPLASH1_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBakcground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBakcground);
  auto *p = new GSplashProcess();
  aGameEngine->AddProcess(p);
}

GSplashState::~GSplashState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GSplashState::Render() {
  gSoundPlayer.PlayMusic(SONG0_XM);
  gDisplay.renderBitmap->CopyPixels(mBakcground);
}