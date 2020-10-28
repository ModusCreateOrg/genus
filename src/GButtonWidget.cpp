#include "Game.h"
#include "GButtonWidget.h"

GButtonWidget::GButtonWidget(const char *aText, TInt aState) : BButtonWidget(aText, COLOR_TEXT, COLOR_TEXT_BG) {
  mState = aState;
}

TInt GButtonWidget::Render(TInt aX, TInt aY) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);
  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(
      ENull,
      STR_RIGHT_ARROW,
      f,
      aX - 16, aY,
      gWidgetTheme.GetInt(WIDGET_TEXT_BG),
      COLOR_TEXT_SHADOW,
      COLOR_TEXT_TRANSPARENT
    );
  }

  gDisplay.renderBitmap->DrawStringShadow(
    ENull,
    mText,
    f,
    aX, aY,
    COLOR_TEXT, //gWidgetTheme.GetInt(WIDGET_TITLE_FG),
    COLOR_TEXT_SHADOW,
    COLOR_TEXT_TRANSPARENT,
    -6
  );

  return f->mHeight + 10;
}

void GButtonWidget::Select() {
  if (mState > -1) {
    gGame->SetState(mState);
  }
#ifdef ENABLE_AUDIO
  gSoundPlayer.SfxMenuIn();
#endif
}
