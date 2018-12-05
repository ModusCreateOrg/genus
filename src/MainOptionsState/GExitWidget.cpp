#include "GExitWidget.h"
#include "Game.h"
#include "THighScoreTable.h"

// special characters
static const char *STR_RIGHT_ARROW = "\xe";

GExitWidget::GExitWidget() : BButtonWidget("EXIT", COLOR_TEXT, COLOR_TEXT_BG) {}

GExitWidget::~GExitWidget() {}

TInt GExitWidget::Render(TInt aX, TInt aY) {
#ifdef __XTENSA__
  aY += 16;
#else
  aY += 20;
#endif

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

  return f->mHeight - 4;
}

void GExitWidget::Select() {
  gGame->SetState(GAME_STATE_MAIN_MENU);
}
