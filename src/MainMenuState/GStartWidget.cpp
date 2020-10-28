#include "Game.h"
#include "GStartWidget.h"
#include "GMainMenuProcess.h"

GStartWidget::GStartWidget(GMainMenuProcess *aProcess) : GButtonWidget("START") {
  mProcess = aProcess;
  mHeight = 24;
}


TInt GStartWidget::Render(TInt aX, TInt aY) {
  GButtonWidget::Render(aX, aY);
  return gWidgetTheme.GetFont(WIDGET_TITLE_FONT)->mHeight + 10;
}

void GStartWidget::Select() {
  gSoundPlayer.SfxMenuAccept();

  if (gOptions->gameProgress.savedState) {
    mProcess->SwitchContainer(1);
    return;
  }

  gGame->SetState(GAME_STATE_GAME);
}
