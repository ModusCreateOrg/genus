#include "GCancelResetWidget.h"
#include "Game.h"
#include "THighScoreTable.h"

GCancelResetWidget::GCancelResetWidget() : BButtonWidget("CANCEL", COLOR_TEXT, COLOR_TEXT_BG) {}

GCancelResetWidget::~GCancelResetWidget() {}

TInt GCancelResetWidget::Render(TInt aX, TInt aY) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);
  aY -= f->mHeight - 4;
  aX += 60;

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

void GCancelResetWidget::Select() {
  // Go Back
  gGame->SetState(GAME_STATE_MAIN_OPTIONS);
}
