#ifndef GENUS_GGAMEOVERPROCESS_H
#define GENUS_GGAMEOVERPROCESS_H

#include <BProcess.h>

class GGameOverProcess : public BProcess {
public:
  GGameOverProcess();
  ~GGameOverProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  TInt mFrameCounter;
};

#endif //GENUS_GGAMEOVERPROCESS_H
