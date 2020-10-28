#ifndef GENUS_GPAUSEMODAL_H
#define GENUS_GPAUSEMODAL_H

#include "Widgets.h"
#include "GSaveWidget.h"
#include "GResumeWidget.h"
#include "GMusicWidget.h"
#include "GSfxWidget.h"

class GPauseModal : public GDialogWidget {
  public:
    GPauseModal(TInt aX, TInt aY) : GDialogWidget("GAME PAUSED", aX, aY) {
      AddWidget((BWidget &) *new GMusicWidget());
      AddWidget((BWidget &) *new GSfxWidget());
      AddWidget((BWidget &) *new GSaveWidget());
      AddWidget((BWidget &) *new GResumeWidget());

      mTimer = 30;
    }

    TInt Render(TInt aX, TInt aY) OVERRIDE {
      TInt color = gWidgetTheme.GetInt(WIDGET_TEXT_BG);;
      const BFont *f = gWidgetTheme.GetFont(WIDGET_TITLE_FONT);
      const TInt x = (SCREEN_WIDTH - (strlen(mTitle) * f->mWidth)) / 2;

      if (--mTimer < 0) {
        mTimer = 30;
      } else if (mTimer >= 15) {
        color = gWidgetTheme.GetInt(WIDGET_TEXT_BG);
      } else if (mTimer < 15) {
        color = gWidgetTheme.GetInt(WIDGET_TITLE_FG);
      }

      gDisplay.renderBitmap->DrawStringShadow(
        ENull,
        mTitle,
        f,
        aX + x, aY + 16,
        color,
        COLOR_TEXT_SHADOW,
        (TInt16)gWidgetTheme.GetInt(WIDGET_TITLE_BG),
        -6
      );

      return GDialogWidget::Render(aX, aY);
    }

    TInt mTimer;
};

#endif //GENUS_GPAUSEMODAL_H
