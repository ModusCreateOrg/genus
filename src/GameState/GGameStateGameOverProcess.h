#ifndef GENUS_GGAMEOVERPROCESS_H
#define GENUS_GGAMEOVERPROCESS_H

#include <BProcess.h>

class GGameStateGameOverProcess : public BProcess {
public:
  GGameStateGameOverProcess();
  ~GGameStateGameOverProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  void Render();
protected:
  TInt mTextColor;
  TInt mFrameCounter;
  enum {
    STATE_FADEIN,
    STATE_FADEOUT,
  } mState;
};

#endif //GENUS_GGAMEOVERPROCESS_H
