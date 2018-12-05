#include "GBrightnessWidget.h"
#include "Game.h"

static const TRange brightness_options = {
  0, 8, 1
};

GBrightnessWidget::GBrightnessWidget() : GSoundSliderWidget("SCREEN", &brightness_options, COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
}

GBrightnessWidget::~GBrightnessWidget() {}

TInt GBrightnessWidget::Render(TInt aX, TInt aY) {
  mSelectedValue = MAX(0, (gOptions->brightness / 0.125) - 2);
  return GSoundSliderWidget::Render(aX, aY);
}

void GBrightnessWidget::Select(TInt aVal) {
  aVal = MAX(1, aVal + 2);
  gOptions->brightness = aVal * 0.125f;
  gOptions->Save();

#ifdef __XTENSA__
  // This widget shouldn't be added to non-xtensa devices
  // but let's be safe just in case
  gDisplay.SetBrightness(0x1fff * gOptions->brightness);
#endif
}
