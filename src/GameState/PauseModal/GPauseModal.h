#ifndef GENUS_GPAUSEMODAL_H
#define GENUS_GPAUSEMODAL_H

#include "Widgets.h"
#include "GSaveWidget.h"
#include "GResumeWidget.h"
#include "GMusicWidget.h"
#include "GSfxWidget.h"
#include "GBrightnessWidget.h"

class GPauseModal : public GDialogWidget {
  public:
    GPauseModal(TInt aX, TInt aY) : GDialogWidget("Pause", aX, aY) {
#ifdef __XTENSA__
      AddWidget((BWidget &) *new GBrightnessWidget());
#endif
      AddWidget((BWidget &) *new GMusicWidget());
      AddWidget((BWidget &) *new GSfxWidget());
      AddWidget((BWidget &) *new GSaveWidget());
      AddWidget((BWidget &) *new GResumeWidget());
    }

    ~GPauseModal() {}
};

#endif //GENUS_GPAUSEMODAL_H
