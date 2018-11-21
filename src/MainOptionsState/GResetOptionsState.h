#ifndef GENUS_GRESETOPTIONSSTATE_H
#define GENUS_GRESETOPTIONSSTATE_H

#include <BGameEngine.h>

class GResetOptionsState : public BGameEngine {
public:
  GResetOptionsState();

  virtual ~GResetOptionsState();
private:
    BFont *mFont16, *mFont8;
};

#endif //GENUS_GRESETOPTIONSSTATE_H
