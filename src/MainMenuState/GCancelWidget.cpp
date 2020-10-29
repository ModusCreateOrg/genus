#include "GCancelWidget.h"
#include "Game.h"
#include "THighScoreTable.h"

// special characters

GCancelWidget::GCancelWidget(GMainMenuProcess *aProcess) : BButtonWidget("EXIT", COLOR_TEXT, COLOR_TEXT_BG) {
  mProcess = aProcess;
}

GCancelWidget::~GCancelWidget() {}

TInt GCancelWidget::Render(TInt aX, TInt aY) {

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
      COLOR_TEXT_TRANSPARENT);

  return f->mHeight - 4;
}

void GCancelWidget::Select() {
  mProcess->SwitchContainer(0);
  gSoundPlayer.SfxMenuCancel();
}
