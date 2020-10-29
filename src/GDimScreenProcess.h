#ifndef GENUS_GDIMSCREENPROCESS_H
#define GENUS_GDIMSCREENPROCESS_H

#include "GGame.h"

class GDimScreenProcess : public BProcess {
  public:
    GDimScreenProcess() : BProcess() {
      ResetTimer();
    }

    ~GDimScreenProcess() {}

    void ResetTimer() {
      mTimer = 300; // 10s
    }

    TBool RunBefore() {
      return ETrue;
    }

    TBool RunAfter() {
#ifdef __XTENSA__
      if (gControls.IsPressed(BUTTON_JOY_ANY)) {
        gDisplay.SetBrightness(MAX(MIN_BRIGHTNESS, MAX_BRIGHTNESS * gOptions->brightness));
        ResetTimer();
      } else {
        mTimer--;
        if (mTimer < 0) {
          gDisplay.SetBrightness(MIN_BRIGHTNESS);
          ResetTimer();
        }
      }
#endif
      return ETrue;
    }

    TInt16 mTimer;
};

#endif //GENUS_GDIMSCREENPROCESS_H
