#include "Game.h"
#include <string.h>

static const TInt TIMEOUT = 30 * 4;

class GHighScoresProcess : public BProcess {
public:
  GHighScoresProcess() : BProcess() {
    mTimer      = TIMEOUT;
    mFont8  = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
    mFont16 = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
    mHighScoreTable.Load();
  }

  ~GHighScoresProcess() {
    delete mFont16;
    delete mFont8;
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

  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    static const TInt16 TITLE_Y      = 10;
    static const TInt16 HIGHSCORES_X = 50;
    static const TInt16 HIGHSCORES_Y = TITLE_Y + 32;

    if (--mTimer < 0 || gControls.WasPressed(BUTTON_START)) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    TInt y = TITLE_Y;
    y += CenterText16("HIGH SCORES", y);
    switch (gOptions->difficulty) {
      case 1:
        y += CenterText8("Easy", y);
        break;
      case 2:
        y += CenterText8("Moderate", y);
        break;
      case 3:
        y += CenterText8("Hard", y);
        break;
      default:
        Panic("GGameOverProcess: invalid difficulty: %d\n", gOptions->difficulty);
    }
    y += 16;
    mHighScoreTable.Render(gOptions->difficulty, 10, HIGHSCORES_X, y, mFont16, COLOR_TEXT);
    if (gControls.WasPressed(BUTTON_START)) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }

private:
  TInt            mTimer;
  BFont           *mFont8, *mFont16;
  THighScoreTable mHighScoreTable;
  BBitmap         *mBackground;
};

class GHighScoresPlayfield : public BPlayfield {
public:
  GHighScoresPlayfield() {
    gResourceManager.LoadBitmap(MENU_BACKGROUND_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
    gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
    gDisplay.SetColor(COLOR_TEXT_BG, 0, 0, 0);
  }

  virtual ~GHighScoresPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }

public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }

public:
  BBitmap *mBackground;
};

GHighScoresState::GHighScoresState() : BGameEngine(gViewPort) {
  mPlayfield = new GHighScoresPlayfield();
  AddProcess(new GHighScoresProcess());
}

GHighScoresState::~GHighScoresState() {
  mFont = ENull;
  delete mPlayfield;
  mPlayfield = ENull;
}

void GHighScoresState::PostRender() {
}
