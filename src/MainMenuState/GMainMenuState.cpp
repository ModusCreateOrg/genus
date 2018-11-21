#include "Game.h"

static const TInt TIMEOUT = 30 * 5;

class GMainMenuProcess : public BProcess {
public:
  GMainMenuProcess() : BProcess() {
    mTimer = TIMEOUT;
  }

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_START)) {
      printf("Difficulty: %d\n", gOptions->difficulty);
      gGame->SetState(GAME_STATE_GAME);
      return EFalse;
    } else if (gControls.WasPressed(BUTTON_MENU)) {
      gGame->SetState(GAME_STATE_MAIN_OPTIONS);
      return EFalse;
    }
    mTimer--;
    if (mTimer < 0) {
      gGame->SetState(GAME_STATE_HIGH_SCORES);
      return EFalse;
    }
    return ETrue;
  }

private:
  TInt mTimer;
};

class GMainMenuPlayfield : public BPlayfield {
public:
  GMainMenuPlayfield() {
    mFont8 = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
    mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
    gResourceManager.LoadBitmap(MENU_BACKGROUND_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gResourceManager.LoadBitmap(GENUS_LOGO_BMP, PLAYER_SLOT, IMAGE_ENTIRE);
    mLogo = gResourceManager.GetBitmap(PLAYER_SLOT);
    gDisplay.SetPalette(mBackground);
    mState = 0;
    gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
    gDisplay.SetColor(COLOR_TEXT_BG, 0, 0, 0);
  }

  virtual ~GMainMenuPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }

public:
  TInt CenterText8(const char *s, TInt aY, TInt aColor = COLOR_TEXT, TInt aBackground = -1) {
    TInt x = TInt((320 - (strlen(s) * 8)) / 2);
    gDisplay.renderBitmap->DrawString(ENull, s, mFont8, x, aY, aColor, aBackground);
    return 8;
  }
  TInt CenterText16(const char *s, TInt aY, TInt aColor = COLOR_TEXT, TInt aBackground = -1) {
    TInt width = aBackground == -1 ? 12 : 16;
    TInt x     = TInt((320 - (strlen(s) * width)) / 2);
    if (aBackground != -1) {
      gDisplay.renderBitmap->DrawString(ENull, s, mFont16, x, aY, aColor, aBackground);
    } else {
      gDisplay.renderBitmap->DrawString(ENull, s, mFont16, x, aY, aColor, aBackground, -4);
    }
    return 16;
  }

public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
    TInt w = mLogo->Width(), h = mLogo->Height();
    TInt x = (320 - w) / 2 + ((mState & 1) ? -1 : 1);
    TInt y = 60 + ((mState & 1) ? -1 : 1);
    gDisplay.renderBitmap->DrawBitmapTransparent(
      ENull,                      // ViewPort
      mLogo,                      // bitmap
      TRect(0, 0, w - 1, h - 1),  // src rect
      x, y                        // destination point
    );
    y = 160;
    y += CenterText16("Press Menu for Options", y, COLOR_TEXT) + 8;
    CenterText16("Or Start to play", y, COLOR_TEXT);
    mState++;
  }

public:
  BFont   *mFont8, *mFont16;
  BBitmap *mBackground;
  BBitmap *mLogo;
  TInt    mState;
};

GMainMenuState::GMainMenuState() : BGameEngine(gViewPort) {
  mPlayfield = new GMainMenuPlayfield();
  auto *p = new GMainMenuProcess();
  AddProcess(p);
}

GMainMenuState::~GMainMenuState() {
  delete mPlayfield;
  mPlayfield = ENull;
}

