#include "Game.h"
#include "GConfirmResetWidget.h"
#include "GCancelResetWidget.h"


class ResetOptionsContainer : public BDialogWidget {
public:
    ResetOptionsContainer(TInt aX, TInt aY) : BDialogWidget("RESET GAME", aX, aY) {
      AddWidget((BWidget &) *new GConfirmResetWidget());
      AddWidget((BWidget &) *new GCancelResetWidget());
    }

    void Run() {
      for (BWidget *w = (BWidget *) mList.First(); !mList.End(w); w = (BWidget *) mList.Next(w)) {
        w->Run();
      }
      if (gControls.WasPressed(JOYRIGHT)) {
        mCurrentWidget->Deactivate();
        if (mCurrentWidget == mList.First()) {
          mCurrentWidget = (BWidget *) mList.Last();
        } else {
          mCurrentWidget = (BWidget *) mList.Prev(mCurrentWidget);
        }
        mCurrentWidget->Activate();

        // reset dKeys so next state doesn't react to any keys already pressed
        gControls.dKeys = 0;
      }
      if (gControls.WasPressed(JOYLEFT)) {
        mCurrentWidget->Deactivate();
        if (mCurrentWidget == mList.Last()) {
          mCurrentWidget = (BWidget *) mList.First();
        } else {
          mCurrentWidget = (BWidget *) mList.Next(mCurrentWidget);
        }
        mCurrentWidget->Activate();

        // reset dKeys so next state doesn't react to any keys already pressed
        gControls.dKeys = 0;
      }
    }
};

class GResetOptionsProcess : public BProcess {
public:
    GResetOptionsProcess() : BProcess() {
      mContainer = new ResetOptionsContainer(50, 160);
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
      gResourceManager.LoadBitmap(MAIN_OPTIONS_RESET1_BMP, BKG_SLOT, IMAGE_ENTIRE);
      mBackground = gResourceManager.GetBitmap(BKG_SLOT);
      gDisplay.SetPalette(mBackground);
    }

    virtual ~GResetOptionsPlayfield() {
      gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
    }

public:
    void Render() {
      gDisplay.renderBitmap->CopyPixels(mBackground);

      const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);
      const char* str1 = "Are you sure you want to";
      const char* str2 = "reset all options and";
      const char* str3 = "highscores?";
      const TInt charWidth = f->mWidth - 6;

      gDisplay.renderBitmap->DrawStringShadow(ENull,
          str1,
          f,
          (SCREEN_WIDTH - strlen(str1) * charWidth) / 2, 100,
          gWidgetTheme.GetInt(WIDGET_TITLE_FG),
          COLOR_TEXT_SHADOW,
          gWidgetTheme.GetInt(WIDGET_TITLE_BG),
          -6);

      gDisplay.renderBitmap->DrawStringShadow(ENull,
          str2,
          f,
          (SCREEN_WIDTH - strlen(str2) * charWidth) / 2, 120,
          gWidgetTheme.GetInt(WIDGET_TITLE_FG),
          COLOR_TEXT_SHADOW,
          gWidgetTheme.GetInt(WIDGET_TITLE_BG),
          -6);

      gDisplay.renderBitmap->DrawStringShadow(ENull,
          str3,
          f,
          (SCREEN_WIDTH - strlen(str3) * charWidth) / 2, 140,
          gWidgetTheme.GetInt(WIDGET_TITLE_FG),
          COLOR_TEXT_SHADOW,
          gWidgetTheme.GetInt(WIDGET_TITLE_BG),
          -6);
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


