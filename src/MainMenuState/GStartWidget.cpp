#include "Game.h"
#include "GStartWidget.h"
#include "GMainMenuProcess.h"

GStartWidget::GStartWidget(GMainMenuProcess *aProcess) : BButtonWidget("START", COLOR_TEXT, COLOR_TEXT_BG) {
  mProcess = aProcess;
}

GStartWidget::~GStartWidget() {}

TInt GStartWidget::Render(TInt aX, TInt aY) {
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

void GStartWidget::Select() {
  gSoundPlayer.SfxMenuAccept();

  if (gOptions->gameProgress.savedState) {
    mProcess->SwitchContainer(1);
    return;
  }

  gGame->SetState(GAME_STATE_GAME);
}
