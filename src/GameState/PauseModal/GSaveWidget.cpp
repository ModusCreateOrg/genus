#include "Game.h"
#include "GGameState.h"
#include "GSaveWidget.h"



GSaveWidget::GSaveWidget() : BButtonWidget("SAVE GAME", COLOR_TEXT, COLOR_TEXT_BG) {}

GSaveWidget::~GSaveWidget() {}

TInt GSaveWidget::Render(TInt aX, TInt aY) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(
      ENull,
      STR_RIGHT_ARROW,
      f,
      aX - 16, aY,
      gWidgetTheme.GetInt(WIDGET_TEXT_BG),
      COLOR_TEXT_SHADOW,
      -1
    );
  }

  gDisplay.renderBitmap->DrawStringShadow(
    ENull,
    mText,
    f,
    aX, aY,
    gWidgetTheme.GetInt(WIDGET_TITLE_FG),
    COLOR_TEXT_SHADOW,
    gWidgetTheme.GetInt(WIDGET_TITLE_BG),
    -6
  );

  return f->mHeight - 4;
}

void GSaveWidget::Select() {
  if (gGame->GetState() != GAME_STATE_GAME) {
    return;
  }

  ((GGameState*) gGameEngine)->SaveState();
  // Simulate start button press
  gControls.dKeys |= BUTTON_START;
  printf("SAVE\n");
  gSoundPlayer.SfxSaveGame();
}
