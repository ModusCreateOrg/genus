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
  mSelectedValue = gOptions->brightness / 0.125;
  return GSoundSliderWidget::Render(aX, aY);
}

void GBrightnessWidget::Select(TInt aVal) {
  gOptions->brightness = aVal * 0.125;
  gOptions->Save();

  // TODO: @Jay to implement SetBrightness
  // gDisplay.SetBrightness(gOptions->brightness);
}
