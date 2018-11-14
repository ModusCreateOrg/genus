#include "Game.h"
#include "GConfirmResetWidget.h"


class ResetOptionsContainer : public BDialogWidget {
public:
    ResetOptionsContainer(TInt aX, TInt aY) : BDialogWidget("RESET GAME", aX, aY) {
      AddWidget((BWidget &) *new GConfirmResetWidget());
    }
};

class GResetOptionsProcess : public BProcess {
public:
    GResetOptionsProcess() : BProcess() {
      mContainer = new ResetOptionsContainer(10, 60);
    }

    ~GResetOptionsProcess() {
      delete mContainer;
    }

public:
    TBool RunBefore() {
      mContainer->Render(30, 20);
      mContainer->Run();
      return ETrue;
    }

    TBool RunAfter() {
      if (gControls.WasPressed(BUTTON_START)) {
        gGame->SetState(GAME_STATE_MAIN_MENU);
        return EFalse;
      } else if (gControls.WasPressed(BUTTON_MENU)) {
        gGame->SetState(GAME_STATE_CREDITS);
        return EFalse;
      }
      return ETrue;
    }

protected:
    ResetOptionsContainer *mContainer;
    BFont *mFont16;
};

class GResetOptionsPlayfield : public BPlayfield {
public:
    GResetOptionsPlayfield() {
      gResourceManager.LoadBitmap(MAIN_OPTIONS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
      mBackground = gResourceManager.GetBitmap(BKG_SLOT);
      gDisplay.SetPalette(mBackground);
    }

    virtual ~GResetOptionsPlayfield() {
      gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
    }

public:
    void Render() {
      gDisplay.renderBitmap->CopyPixels(mBackground);
    }

public:
    BBitmap *mBackground;
};


GResetOptionsState::GResetOptionsState() : BGameEngine(gViewPort) {
  gResourceManager.LoadBitmap(CHARSET_8X8_BMP, FONT_8x8_SLOT);
  gResourceManager.LoadBitmap(CHARSET_16X16_BMP, FONT_16x16_SLOT);
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

  mPlayfield = new GResetOptionsPlayfield();

  auto *p = new GResetOptionsProcess();
  AddProcess(p);
  gSoundPlayer.PlayMusic(SONG0_XM);
  gWidgetTheme.Configure(
      WIDGET_TEXT_FONT, mFont16,
      WIDGET_TEXT_FG, COLOR_TEXT,
      WIDGET_TEXT_BG, COLOR_TEXT_BG,
      WIDGET_TITLE_FONT, mFont16,
      WIDGET_TITLE_FG, COLOR_TEXT,
      WIDGET_TITLE_BG, -1,
      WIDGET_WINDOW_BG, gDisplay.renderBitmap->TransparentColor(),
      WIDGET_WINDOW_FG, gDisplay.renderBitmap->TransparentColor(),
      WIDGET_SLIDER_FG, COLOR_TEXT_BG,
      WIDGET_SLIDER_BG, COLOR_TEXT,
      WIDGET_END_TAG);

  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_BG, 255, 92, 93);
}

GResetOptionsState::~GResetOptionsState() {
  gResourceManager.ReleaseBitmapSlot(FONT_8x8_SLOT);
  gResourceManager.ReleaseBitmapSlot(FONT_16x16_SLOT);
  delete mFont16;
}


