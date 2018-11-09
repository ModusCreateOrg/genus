#include "GDifficulty.h"

static const TSelectOption difficulty_options[] = {
    {"Beginner", 1},
    {"Intermediate", 2},
    {"Hard", 3},
    TSELECT_END_OPTIONS
};

GDifficulty::GDifficulty() : BSelectWidget("Difficulty", &difficulty_options[0], COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
  mSelectedIndex = gOptions->difficulty;
}

GDifficulty::~GDifficulty() {
  //
}

void GDifficulty::Set(TInt aIndex) {
  mSelectedIndex = aIndex;
}

TInt GDifficulty::Render(TInt aX, TInt aY) {
  TInt h = 0;
  TInt dy = BSelectWidget::Render(aX, aY);
  h += dy;
  return h;
}

void GDifficulty::Select(TInt aIndex) {
  gOptions->difficulty = aIndex;
  gOptions->Save();
}
