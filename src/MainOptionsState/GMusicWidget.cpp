#include "GMusicWidget.h"
#include "Game.h"

static const TRange music_options = {
  0, 100, 5, 100
};

GMusicWidget::GMusicWidget() : BSliderWidget("Music", &music_options, COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
  mSelectedValue = gOptions->music * music_options.precision;
}

GMusicWidget::~GMusicWidget() {

}

void GMusicWidget::Set(TInt aVal) {
  mSelectedValue = aVal;
}

TInt GMusicWidget::Render(TInt aX, TInt aY) {
  TInt h = 0;
  TInt dy = BSliderWidget::Render(aX, aY);
  h += dy;
  return h;
}

void GMusicWidget::Select(TInt aVal) {
  gOptions->music = aVal / TFloat(music_options.precision);
  gOptions->muted = EFalse;
  gOptions->Save();
  gSoundPlayer.SetMusicVolume(gOptions->music);
  gSoundPlayer.MuteMusic(gOptions->muted);
}
