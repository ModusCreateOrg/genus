#include "GRulesWidget.h"
#include "Game.h"

GRulesWidget::GRulesWidget() : BButtonWidget("RULES", COLOR_TEXT, COLOR_TEXT_BG) {}

GRulesWidget::~GRulesWidget() {}

TInt GRulesWidget::Render(TInt aX, TInt aY) {
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

  return f->mHeight + 10;
}

void GRulesWidget::Select() {
  gGame->SetState(GAME_STATE_RULES);
}
