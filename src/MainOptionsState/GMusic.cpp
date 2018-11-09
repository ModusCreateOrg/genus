#include "GMusic.h"
#include "Game.h"

static const TRange music_options = {
  0, 100, 5, 100
};

GMusic::GMusic() : BSliderWidget("Music", &music_options, COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
  mSelectedValue = gOptions->music;
}

GMusic::~GMusic() {

}

void GMusic::Set(TInt aVal) {
  mSelectedValue = aVal;
}

TInt GMusic::Render(TInt aX, TInt aY) {
  TInt h = 0;
  TInt dy = BSliderWidget::Render(aX, aY);
  h += dy;
  return h;
}

void GMusic::Select(TInt aVal) {
  gOptions->music = aVal;
  gOptions->Save();
  gSoundPlayer.SetVolume(aVal / TFloat(music_options.precision));
}
