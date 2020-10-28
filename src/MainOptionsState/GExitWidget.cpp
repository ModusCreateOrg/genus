#include "GExitWidget.h"
#include "Game.h"
#include "THighScoreTable.h"



GExitWidget::GExitWidget() : BButtonWidget("BACK", COLOR_TEXT, COLOR_TEXT_BG) {}

GExitWidget::~GExitWidget() {}

TInt GExitWidget::Render(TInt aX, TInt aY) {
  aY += 20;

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
      (TInt16)gWidgetTheme.GetInt(WIDGET_TITLE_BG),
      -6);

  return f->mHeight - 4;
}

void GExitWidget::Select() {
  gGame->SetState(GAME_STATE_MAIN_MENU);
  gSoundPlayer.SfxMenuCancel();
}
