#include "Game.h"
#include "GResetOptionsWidget.h"
#include "GResetHighScoresWidget.h"
#include "GResetAllWidget.h"
#include "GCancelResetWidget.h"

class ResetOptionsContainer : public GDialogWidget {
public:
    ResetOptionsContainer(TInt aX, TInt aY) : GDialogWidget("RESET GAME", aX, aY) {
      AddWidget((BWidget &) *new GResetOptionsWidget());
      AddWidget((BWidget &) *new GResetHighScoresWidget());
      AddWidget((BWidget &) *new GResetAllWidget());
      AddWidget((BWidget &) *new GCancelResetWidget());
    }
};

class GResetOptionsProcess : public BProcess {
public:
    GResetOptionsProcess() : BProcess() {
      mContainer = new ResetOptionsContainer(80, 92);
    }

    ~GResetOptionsProcess() {
      delete mContainer;
    }

public:
    TBool RunBefore() {

      return ETrue;
    }

    TBool RunAfter() {
      mContainer->Render(30, 20);
      mContainer->Run();
      if (gControls.WasPressed(BUTTON_MENU | BUTTON_START)) {
        gGame->SetState(GAME_STATE_MAIN_OPTIONS);
        gSoundPlayer.SfxMenuCancel();
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
    void Render() OVERRIDE {
      gDisplay.renderBitmap->CopyPixels(mBackground);

      const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);
      const char* questionStr = "Choose what to reset";
      const TInt charWidth = f->mWidth - 6;

      gDisplay.renderBitmap->DrawStringShadow(ENull,
          questionStr,
          f,
          (TInt)((SCREEN_WIDTH - strlen(questionStr) * charWidth) / 2),
          80,
          gWidgetTheme.GetInt(WIDGET_TITLE_FG),
          COLOR_TEXT_SHADOW,
          COLOR_TEXT_TRANSPARENT,
          -6
      );
    }

public:
    BBitmap *mBackground;
};


GResetOptionsState::GResetOptionsState() : BGameEngine(gViewPort) {
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

  mPlayfield = new GResetOptionsPlayfield();

  auto *p = new GResetOptionsProcess();
  AddProcess(p);
//  gSoundPlayer.PlayMusic(SONG0_XM);
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
  delete mFont16;
}


