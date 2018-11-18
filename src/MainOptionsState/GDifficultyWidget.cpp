#include "GDifficultyWidget.h"

static const TSelectOption difficulty_options[] = {
    {"Easy", 1},
    {"Normal", 2},
    {"Hard", 3},
    TSELECT_END_OPTIONS
};

GDifficultyWidget::GDifficultyWidget() : BSelectWidget("MODE", &difficulty_options[0], COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
}

GDifficultyWidget::~GDifficultyWidget() {
  //
}

void GDifficultyWidget::Set(TInt aIndex) {
  mSelectedIndex = aIndex;
}

TInt GDifficultyWidget::RenderTitle(TInt aX, TInt aY, TBool aActive) {
  const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);

  if (mActive) {
    gDisplay.renderBitmap->DrawStringShadow(ENull,
        ">",
        f,
        aX - 16, aY,
        gWidgetTheme.GetInt(WIDGET_TEXT_BG),
        COLOR_TEXT_SHADOW,
        -1);
  }

  gDisplay.renderBitmap->DrawStringShadow(ENull,
      mTitle,
      f,
      aX, aY,
      gWidgetTheme.GetInt(WIDGET_TITLE_FG),
      COLOR_TEXT_SHADOW,
      gWidgetTheme.GetInt(WIDGET_TITLE_BG),
      -6);

  return f->mHeight + 4;
}

TInt GDifficultyWidget::Render(TInt aX, TInt aY) {
  mSelectedIndex = gOptions->difficulty;
  aX += 19;
  aY -= 20;

  const BFont *f = gWidgetTheme.GetFont(WIDGET_TEXT_FONT);
  const TInt  fg    = gWidgetTheme.GetInt(WIDGET_TEXT_FG),
              bg    = gWidgetTheme.GetInt(WIDGET_TEXT_BG);
  TInt        ndx   = 0,
              x     = aX;

  while (mOptions[ndx].text) {
    if (ndx != mSelectedIndex) {
      gDisplay.renderBitmap->DrawStringShadow(ENull,
                                        mOptions[ndx].text,
                                        f,
                                        x + aX, aY,
                                        fg, COLOR_TEXT_SHADOW, -1, -6);
    } else {
      gDisplay.renderBitmap->DrawStringShadow(ENull,
                                        mOptions[ndx].text,
                                        f,
                                        x + aX, aY,
                                        bg, COLOR_TEXT_SHADOW, -1, -6);
    }

    x += f->mWidth * strlen(mOptions[ndx].text) - (14 * (ndx + 1));
    ndx++;
  }

  return f->mHeight - 4;
}

void GDifficultyWidget::Select(TInt aIndex) {
  gOptions->difficulty = aIndex;
  gOptions->Save();
}
