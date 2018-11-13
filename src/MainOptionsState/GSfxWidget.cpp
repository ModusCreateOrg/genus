#include "GSfxWidget.h"
#include "Game.h"

static const TRange sfx_options = {
  0, 100, 5, 100
};

GSfxWidget::GSfxWidget() : BSliderWidget("Sfx", &sfx_options, COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
  mSelectedValue = gOptions->sfx * sfx_options.precision;
}

GSfxWidget::~GSfxWidget() {

}

void GSfxWidget::Set(TInt aVal) {
  mSelectedValue = aVal;
}

TInt GSfxWidget::Render(TInt aX, TInt aY) {
  TInt h = 0;
  TInt dy = BSliderWidget::Render(aX, aY);
  h += dy;
  return h;
}

void GSfxWidget::Select(TInt aVal) {
  gOptions->sfx = aVal / TFloat(sfx_options.precision);
  gOptions->muted = EFalse;
  gOptions->Save();
  gSoundPlayer.SetEffectsVolume(gOptions->sfx);
  gSoundPlayer.MuteMusic(gOptions->muted);
  gSoundPlayer.PlaySound(/*SFX_SCORE_COMBO_WAV*/5, 0, EFalse);
}
