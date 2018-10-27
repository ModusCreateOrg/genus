#include "GMusic.h"
#include "Game.h"

static const TSelectOption music_options[] = {
    {"On", 1},
    {"Off", 2},
    TSELECT_END_OPTIONS
};

GMusic::GMusic() : BSelectWidget("Music", &music_options[0], COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
}

GMusic::~GMusic() {

}

TInt GMusic::Render(TInt aX, TInt aY) {
  TInt h = 0;
  TInt dy = BSelectWidget::Render(aX, aY);
  h += dy;
  return h;
}

void GMusic::Select(TInt aIndex) {
  printf("Music Selected %d\n", aIndex);
}
