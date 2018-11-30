#include "Game.h"
#include "GDifficultyWidget.h"
#include "GMusicWidget.h"
#include "GSfxWidget.h"
#include "GResetWidget.h"
#include "GExitWidget.h"


class OptionsContainer : public BDialogWidget {
public:
    OptionsContainer(TInt aX, TInt aY) : BDialogWidget("Options", aX, aY) {
      AddWidget((BWidget &) *new GDifficultyWidget());
      AddWidget((BWidget &) *new GMusicWidget());
      AddWidget((BWidget &) *new GSfxWidget());
      AddWidget((BWidget &) *new GResetWidget());
      AddWidget((BWidget &) *new GExitWidget());
    }

    TBool Run() {
      if (BDialogWidget::Run()) {
        gSoundPlayer.SfxMenuNav();
      }
      return ETrue;
    }
};

class GMainOptionsProcess : public BProcess {
public:
    GMainOptionsProcess() : BProcess() {
      mContainer = new OptionsContainer(10, 60);
    }

    ~GMainOptionsProcess() {
      delete mContainer;
    }

public:
    TBool RunBefore() {
      mContainer->Render(30, 20);
      mContainer->Run();
      return ETrue;
    }

    TBool RunAfter() {
      if (gControls.WasPressed(BUTTON_MENU | BUTTON_START)) {
        gGame->SetState(GAME_STATE_MAIN_MENU);
        return EFalse;
      }
      return ETrue;
    }

protected:
    OptionsContainer *mContainer;
    BFont *mFont16;
};

class GMainOptionsPlayfield : public BPlayfield {
public:
    GMainOptionsPlayfield() {
      gResourceManager.LoadBitmap(MAIN_OPTIONS1_BMP, BKG_SLOT, IMAGE_ENTIRE);
      mBackground = gResourceManager.GetBitmap(BKG_SLOT);
      gDisplay.SetPalette(mBackground);
    }

    virtual ~GMainOptionsPlayfield() {
      gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
    }

public:
    void Render() {
      gDisplay.renderBitmap->CopyPixels(mBackground);
    }

public:
    BBitmap *mBackground;
};


GMainOptionsState::GMainOptionsState() : BGameEngine(gViewPort) {
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

  mPlayfield = new GMainOptionsPlayfield();

  auto *p = new GMainOptionsProcess();
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

GMainOptionsState::~GMainOptionsState() {
  delete mFont16;
}


