#include "GResetAllWidget.h"
#include "Game.h"
#include "THighScoreTable.h"

GResetAllWidget::GResetAllWidget() : BButtonWidget("EVERYTHING", COLOR_TEXT, COLOR_TEXT_BG) {}

GResetAllWidget::~GResetAllWidget() {}

TInt GResetAllWidget::Render(TInt aX, TInt aY) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(ENull,
        "\xe",
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

  return f->mHeight << 1;
}

void GResetAllWidget::Select() {
  // Reset High Scores and All
  THighScoreTable highScoreTable;
  highScoreTable.Reset();
  gOptions->Reset();

  // Play notification sound
  gSoundPlayer.PlaySound(/*SFX_SCORE_COMBO_WAV*/5, 0, EFalse);

  // Go Back
  gGame->SetState(GAME_STATE_MAIN_OPTIONS);

  // Make sure we hear the reset in music volume immediately
  gSoundPlayer.SetMusicVolume(gOptions->music);
}
