#include "GResetHighScoresWidget.h"
#include "Game.h"
#include "THighScoreTable.h"



GResetHighScoresWidget::GResetHighScoresWidget() : BButtonWidget("HIGH SCORES", COLOR_TEXT, COLOR_TEXT_BG) {}

GResetHighScoresWidget::~GResetHighScoresWidget() {}

TInt GResetHighScoresWidget::Render(TInt aX, TInt aY) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(ENull,
        STR_RIGHT_ARROW,
        f,
        aX - 16, aY,
        (TInt16)gWidgetTheme.GetInt(WIDGET_TEXT_BG),
        COLOR_TEXT_SHADOW,
        COLOR_TEXT_TRANSPARENT);
  }

  gDisplay.renderBitmap->DrawStringShadow(ENull,
      mText,
      f,
      aX, aY,
      (TInt16)gWidgetTheme.GetInt(WIDGET_TITLE_FG),
      COLOR_TEXT_SHADOW,
      COLOR_TEXT_TRANSPARENT,
      -6);

  return f->mHeight << 1;
}

void GResetHighScoresWidget::Select() {
  // Reset High Scores
  THighScoreTable highScoreTable;
  highScoreTable.Reset();

  // Go Back
  gGame->SetState(GAME_STATE_MAIN_OPTIONS);

  // Play notification sound
  gSoundPlayer.SfxMenuAccept();
}
