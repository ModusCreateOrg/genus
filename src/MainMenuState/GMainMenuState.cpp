#include "Game.h"
#include "GStartWidget.h"
#include "GOptionsWidget.h"
#include "GCreditsWidget.h"

static const TInt TIMEOUT = 30 * 5;

class MenuContainer : public BDialogWidget {
public:
  MenuContainer(TInt aX, TInt aY) : BDialogWidget("Menu", aX, aY) {
    AddWidget((BWidget &) *new GStartWidget());
    AddWidget((BWidget &) *new GOptionsWidget());
    AddWidget((BWidget &) *new GCreditsWidget());
  }
};

class GMainMenuProcess : public BProcess {
public:
  GMainMenuProcess() : BProcess() {
    mTimer = TIMEOUT;
    mContainer = new MenuContainer(0, 0);
  }

  ~GMainMenuProcess() {
    delete mContainer;
  }

public:
  TBool RunBefore() {
    TUint16 keys = gControls.dKeys;

    mContainer->Render(120, 148);
    mContainer->Run();

    if (keys & (JOYUP | JOYDOWN)) {
      mTimer = TIMEOUT;
      gSoundPlayer.SfxMenuNav();
    }

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
  MenuContainer *mContainer;
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
    TInt x = (SCREEN_WIDTH - w) / 2;
    TInt y = 60 ;

    gDisplay.renderBitmap->DrawBitmapTransparent(
      ENull,                      // ViewPort
      mLogo,                      // bitmap
      TRect(0, 0, w - 1, h - 1),  // src rect
      x, y                        // destination point
    );

    mState++;
  }

public:
  BFont   *mFont8, *mFont16;
  BBitmap *mBackground;
  BBitmap *mLogo;
  TInt    mState;
};

GMainMenuState::GMainMenuState() : BGameEngine(gViewPort) {
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  mPlayfield = new GMainMenuPlayfield();
  auto *p = new GMainMenuProcess();
  mMainMenuProcess = p;

  AddProcess(p);

  gWidgetTheme.Configure(
      WIDGET_TEXT_BG, COLOR_TEXT_BG,
      WIDGET_TITLE_FONT, mFont16,
      WIDGET_TITLE_FG, COLOR_TEXT,
      WIDGET_TITLE_BG, -1,
      WIDGET_WINDOW_BG, gDisplay.renderBitmap->TransparentColor(),
      WIDGET_WINDOW_FG, gDisplay.renderBitmap->TransparentColor(),
      WIDGET_END_TAG);

  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_BG, 255, 92, 93);
}

GMainMenuState::~GMainMenuState() {
  delete mPlayfield;
  delete mFont16;
  mPlayfield = ENull;
}

