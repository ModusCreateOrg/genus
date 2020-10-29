#include "Game.h"
#include "GResumeWidget.h"



GResumeWidget::GResumeWidget() : BButtonWidget("RESUME", COLOR_TEXT, COLOR_TEXT_BG) {}

GResumeWidget::~GResumeWidget() {}

TInt GResumeWidget::Render(TInt aX, TInt aY) {
  aY += 20;

  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(
      ENull,
      STR_RIGHT_ARROW,
      f,
      aX - 16,
      aY,
      gWidgetTheme.GetInt(WIDGET_TEXT_BG),
      COLOR_TEXT_SHADOW,
      COLOR_TEXT_TRANSPARENT
    );
  }

  gDisplay.renderBitmap->DrawStringShadow(
      ENull,
      mText,
      f,
      aX, aY,
      gWidgetTheme.GetInt(WIDGET_TITLE_FG),
      COLOR_TEXT_SHADOW,
      COLOR_TEXT_TRANSPARENT,
      -6
  );

  return f->mHeight - 4;
}

void GResumeWidget::Select() {
  // Simulate start button press
  gControls.dKeys |= BUTTON_START;
  gSoundPlayer.SfxMenuAccept();
}
