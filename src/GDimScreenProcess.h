#ifndef GENUS_GDIMSCREENPROCESS_H
#define GENUS_GDIMSCREENPROCESS_H

#include "GGame.h"

class GDimScreenProcess : public BProcess {
  public:
    GDimScreenProcess() : BProcess() {
      printf("New process\n");
      ResetTimer();
    }

    ~GDimScreenProcess() {
      printf("destroyed process\n");
    }

    void ResetTimer() {
      mTimer = 300; // 10s
    }

    TBool RunBefore() {
      return ETrue;
    }

    TBool RunAfter() {
#ifdef __XTENSA__
      const TBool keysPressed = gControls.CheckPressed(BUTTON_JOY_ANY);

      if (keysPressed) {
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
