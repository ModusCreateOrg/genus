#include "Game.h"
#include <string.h>

static const TInt TIMEOUT = 30 * 4;

class GHighScoresProcess : public BProcess {
public:
  GHighScoresProcess() : BProcess() {
    mTimer = TIMEOUT;
  }

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (--mTimer < 0 || gControls.WasPressed(BUTTON_START)) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }

private:
  TInt mTimer;
};

class GHighScoresPlayfield : public BPlayfield {
public:
  GHighScoresPlayfield() {
    gResourceManager.LoadBitmap(HIGH_SCORES1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    gDisplay.SetPalette(mBackground);
  }

  virtual ~GHighScoresPlayfield() {
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  }

public:
  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
  }

public:
  BBitmap        *mBackground;
};

GHighScoresState::GHighScoresState() : BGameEngine(gViewPort) {
  mPlayfield = new GHighScoresPlayfield();
  auto *p = new GHighScoresProcess();
  AddProcess(p);

  // load high score table
  BStore f("Genus");
  if (!f.Get("high_scores", &mHighScoreTable, sizeof(mHighScoreTable))) {
    mHighScoreTable.Reset();
    f.Set("high_scores", &mHighScoreTable, sizeof(mHighScoreTable));
    printf("Set High Scores\n");
  }

  gResourceManager.LoadBitmap(CHARSET_8X8_BMP, FONT_8x8_SLOT, IMAGE_8x8);
  mFont = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
}

GHighScoresState::~GHighScoresState() {
  delete mFont;
  mFont = ENull;
  delete mPlayfield;
  mPlayfield = ENull;
}

void GHighScoresState::PostRender() {
  gDisplay.SetColor(COLOR_TEXT, 255,255,255);
  BBitmap   *bm = gDisplay.renderBitmap;
  char      buf[40], sbuf[10];
  TInt      y   = 80, x = 110;
  for (TInt i   = 0; i < 10; i++) {
    strcpy(&buf[0], mHighScoreTable.easy[i].name);
    strcat(buf, "  ");
    mHighScoreTable.easy[i].score.ToString(sbuf);
    strcat(buf, sbuf);
    bm->DrawString(gViewPort, buf, mFont, x, y, COLOR_TEXT);
    y += 10;
  }
}
