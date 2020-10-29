#include "GContinueWidget.h"
#include "Game.h"

GContinueWidget::GContinueWidget() : BButtonWidget("CONTINUE", COLOR_TEXT, COLOR_TEXT_BG) {}

GContinueWidget::~GContinueWidget() {}

TInt GContinueWidget::Render(TInt aX, TInt aY) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(ENull,
        STR_RIGHT_ARROW,
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

  return f->mHeight + 10;
}

void GContinueWidget::Select() {
  gGame->SetState(GAME_STATE_GAME);
}
