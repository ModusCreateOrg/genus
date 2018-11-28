#include "GCancelResetWidget.h"
#include "Game.h"
#include "THighScoreTable.h"

GCancelResetWidget::GCancelResetWidget() : BButtonWidget("CANCEL", COLOR_TEXT, COLOR_TEXT_BG) {}

GCancelResetWidget::~GCancelResetWidget() {}

TInt GCancelResetWidget::Render(TInt aX, TInt aY) {
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

void GCancelResetWidget::Select() {
  // Go Back
  gGame->SetState(GAME_STATE_MAIN_OPTIONS);
}
