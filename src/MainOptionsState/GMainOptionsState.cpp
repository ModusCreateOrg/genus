#include "Game.h"

static const TSelectOption difficulty_options[] = {
    {"Beginner", 1},
    {"Intermediate", 2},
    {"Hard", 3},
    TSELECT_END_OPTIONS
};

class Difficulty : public BSelectWidget {
public:
    Difficulty() : BSelectWidget("Difficulty", &difficulty_options[0], COLOR_TEXT, COLOR_TEXT_BG) {
      mHeight = 30;
    }

    ~Difficulty() {
      //
    }

    TInt Render(TInt aX, TInt aY) {
      TInt h = 0;
      TInt dy = BSelectWidget::Render(aX, aY);
      h += dy;
      return h;
    }

public:
    void Select(TInt aIndex) {
      printf("Selected %d\n", aIndex);
    }
};


static const TSelectOption music_options[] = {
    {"On", 1},
    {"Off", 2},
    TSELECT_END_OPTIONS
};

class Music : public BSelectWidget {
public:
    Music() : BSelectWidget("Music", &music_options[0], COLOR_TEXT, COLOR_TEXT_BG) {
      mHeight = 30;
    }

    TInt Render(TInt aX, TInt aY) {
      TInt h = 0;
      TInt dy = BSelectWidget::Render(aX, aY);
      h += dy;
      return h;
    }

public:
    void Select(TInt aIndex) {
      printf("Music Selected %d\n", aIndex);
    }
};

class OptionsContainer : public BContainerWidget {
public:
    OptionsContainer(TInt aX, TInt aY) : BContainerWidget(aX, aY) {
      gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
      gDisplay.SetColor(COLOR_TEXT_BG, 0, 0, 0);
      gDisplay.SetColor(COLOR_MENU_TITLE, 0, 255, 255);
      SetTextColors(COLOR_TEXT, COLOR_TEXT_BG);
      SetTitleColors(COLOR_MENU_TITLE, COLOR_TEXT_BG);
      AddWidget((BWidget &) *new Difficulty());
      AddWidget((BWidget &) *new Music());
    }

public:
protected:
    Difficulty *mDifficulty;
};

class GMainOptionsProcess : public BProcess {
public:
    GMainOptionsProcess() : BProcess() {
      gResourceManager.LoadBitmap(CHARSET_8X8_BMP, FONT_8x8_SLOT);
      mFont8 = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
      gResourceManager.LoadBitmap(CHARSET_16X16_BMP, FONT_16x16_SLOT);
      mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
      BWidget::SetTextFont(mFont8);
      BWidget::SetTitleFont(mFont16);
      mContainer = new OptionsContainer(20, 60);
    }

    ~GMainOptionsProcess() {
      delete mFont16;
      delete mFont8;
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

    }

public:
    void Render() {
      gDisplay.renderBitmap->CopyPixels(mBackground);
    }

public:
    BBitmap *mBackground;
};


GMainOptionsState::GMainOptionsState() : BGameEngine(gViewPort) {
  mPlayfield = new GMainOptionsPlayfield();
  auto *p = new GMainOptionsProcess();
  AddProcess(p);
  gSoundPlayer.PlayMusic(SONG0_XM);
}

GMainOptionsState::~GMainOptionsState() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}


