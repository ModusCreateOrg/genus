#include "Game.h"
#include "GDifficultyWidget.h"
#include "GMusicWidget.h"
#include "GSfxWidget.h"
#include "GResetWidget.h"


class OptionsContainer : public BDialogWidget {
public:
    OptionsContainer(TInt aX, TInt aY) : BDialogWidget("Options", aX, aY) {
      AddWidget((BWidget &) *new GDifficultyWidget());
      AddWidget((BWidget &) *new GMusicWidget());
      AddWidget((BWidget &) *new GSfxWidget());
      AddWidget((BWidget &) *new GResetWidget());
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
      mContainer->Render(0, 0);
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
    OptionsContainer *mContainer;
    BFont *mFont8, *mFont16;
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
  gResourceManager.LoadBitmap(CHARSET_8X8_BMP, FONT_8x8_SLOT);
  mFont8 = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
  gResourceManager.LoadBitmap(CHARSET_16X16_BMP, FONT_16x16_SLOT);
  mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

  mPlayfield = new GMainOptionsPlayfield();

  auto *p = new GMainOptionsProcess();
  AddProcess(p);
  gSoundPlayer.PlayMusic(SONG0_XM);
  gWidgetTheme.Configure(
      WIDGET_TEXT_FONT, mFont8,
      WIDGET_TEXT_FG, COLOR_TEXT,
      WIDGET_TEXT_BG, COLOR_DIALOG_BG,
      WIDGET_TITLE_FONT, mFont16,
      WIDGET_TITLE_FG, COLOR_MENU_TITLE,
      WIDGET_TITLE_BG, COLOR_TEXT_BG,
      WIDGET_WINDOW_BG, COLOR_DIALOG_BG,
      WIDGET_WINDOW_FG, COLOR_DIALOG_FG,
      WIDGET_END_TAG);

  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_BG, 128,128,128);
  gDisplay.SetColor(COLOR_MENU_TITLE, 0, 255, 255);
  gDisplay.SetColor(COLOR_DIALOG_BG, 128,128,128);
  gDisplay.SetColor(COLOR_DIALOG_FG, 255, 0, 0);

}

GMainOptionsState::~GMainOptionsState() {
  gResourceManager.ReleaseBitmapSlot(FONT_8x8_SLOT);
  gResourceManager.ReleaseBitmapSlot(FONT_16x16_SLOT);
  delete mFont16;
  delete mFont8;
}


