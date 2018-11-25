#include "GResetOptionsWidget.h"
#include "Game.h"

GResetOptionsWidget::GResetOptionsWidget() : BButtonWidget("OPTIONS", COLOR_TEXT, COLOR_TEXT_BG) {}

GResetOptionsWidget::~GResetOptionsWidget() {}

TInt GResetOptionsWidget::Render(TInt aX, TInt aY) {
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

void GResetOptionsWidget::Select() {
  // Reset options
  gOptions->Reset();

  // Play notification sound
  gSoundPlayer.SfxOptionSelect();

  // Go Back
  gGame->SetState(GAME_STATE_MAIN_OPTIONS);

  // Make sure we hear the reset in music volume immediately
  gSoundPlayer.SetMusicVolume(gOptions->music);
}
