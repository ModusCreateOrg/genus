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

      return ETrue;
    }

    TInt16 mTimer;
};

#endif //GENUS_GDIMSCREENPROCESS_H
