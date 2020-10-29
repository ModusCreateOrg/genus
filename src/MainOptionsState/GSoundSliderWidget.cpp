#include "GSoundSliderWidget.h"
#include "Game.h"

GSoundSliderWidget::GSoundSliderWidget(char *aTitle, const TRange *aRange, TInt aForeground, TInt aBackground)
    : BSliderWidget(aTitle, aRange, aForeground, aBackground) {
}

GSoundSliderWidget::GSoundSliderWidget(const char *aTitle, const TRange *aRange, TInt aForeground, TInt aBackground)
    : BSliderWidget(aTitle, aRange, aForeground, aBackground) {
}

GSoundSliderWidget::~GSoundSliderWidget() {}

void GSoundSliderWidget::Set(TInt aVal) {
  mSelectedValue = aVal;
}

TInt GSoundSliderWidget::RenderTitle(TInt aX, TInt aY, TBool aActive) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(ENull,
        STR_RIGHT_ARROW,
        f,
        aX - 16, aY,
        (TUint8)gWidgetTheme.GetInt(WIDGET_TEXT_BG),
        COLOR_TEXT_SHADOW,
        COLOR_TEXT_TRANSPARENT);
  }

  gDisplay.renderBitmap->DrawStringShadow(ENull,
      mTitle,
      f,
      aX, aY,
      (TUint8)gWidgetTheme.GetInt(WIDGET_TITLE_FG),
      (TUint8)COLOR_TEXT_SHADOW,
      (TInt16)gWidgetTheme.GetInt(WIDGET_TITLE_BG),
      -6);

  return f->mHeight + 4;
}

TInt GSoundSliderWidget::Render(TInt aX, TInt aY) {
  aX += 82;
  aY -= 20;

  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);
  const TInt  fg = gWidgetTheme.GetInt(WIDGET_SLIDER_FG),
              bg = gWidgetTheme.GetInt(WIDGET_SLIDER_BG);

  for (TInt i = 0; i < 8; i++) {
    gDisplay.renderBitmap->DrawFastVLine(ENull, aX + 1, aY - 1, 16, COLOR_TEXT_SHADOW);
    gDisplay.renderBitmap->DrawFastHLine(ENull, aX + 2, aY + 14, 7, COLOR_TEXT_SHADOW);
    gDisplay.renderBitmap->FillRect(ENull, aX + 2, aY - 2, aX + 9, aY + 13, i < mSelectedValue ? (TUint8)fg : (TUint8)bg);
    aX += 16;
  }

  return f->mHeight - 4;
}
