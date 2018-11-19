#include "GConfirmResetWidget.h"
#include "Game.h"
#include "THighScoreTable.h"

GConfirmResetWidget::GConfirmResetWidget() : BButtonWidget("RESET", COLOR_TEXT, COLOR_TEXT_BG) {}

GConfirmResetWidget::~GConfirmResetWidget() {}

TInt GConfirmResetWidget::Render(TInt aX, TInt aY) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(ENull,
        ">",
        f,
        aX - 16, aY,
        gWidgetTheme.GetInt(WIDGET_TEXT_BG),
        COLOR_TEXT_SHADOW,
        -1);
  }

  gDisplay.renderBitmap->DrawStringShadow(ENull,
      mText,
      f,
      aX, aY,
      gWidgetTheme.GetInt(WIDGET_TITLE_FG),
      COLOR_TEXT_SHADOW,
      gWidgetTheme.GetInt(WIDGET_TITLE_BG),
      -6);

  return f->mHeight - 4;
}

void GConfirmResetWidget::Select() {
  // Reset High Scores and Options
  THighScoreTable highScoreTable;
  highScoreTable.Reset();
  gOptions->Reset();

  // Play notification sound
  gSoundPlayer.PlaySound(/*SFX_SCORE_COMBO_WAV*/5, 0, EFalse);

  // Go Back
  gGame->SetState(GAME_STATE_MAIN_OPTIONS);
}
