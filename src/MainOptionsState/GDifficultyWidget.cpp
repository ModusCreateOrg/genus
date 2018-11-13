#include "GDifficultyWidget.h"

static const TSelectOption difficulty_options[] = {
    {"Beginner", 1},
    {"Intermediate", 2},
    {"Hard", 3},
    TSELECT_END_OPTIONS
};

GDifficultyWidget::GDifficultyWidget() : BSelectWidget("Difficulty", &difficulty_options[0], COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
  mSelectedIndex = gOptions->difficulty;
}

GDifficultyWidget::~GDifficultyWidget() {
  //
}

void GDifficultyWidget::Set(TInt aIndex) {
  mSelectedIndex = aIndex;
}

TInt GDifficultyWidget::Render(TInt aX, TInt aY) {
  TInt h = 0;
  TInt dy = BSelectWidget::Render(aX, aY);
  h += dy;
  return h;
}

void GDifficultyWidget::Select(TInt aIndex) {
  gOptions->difficulty = aIndex;
  gOptions->Save();
}
