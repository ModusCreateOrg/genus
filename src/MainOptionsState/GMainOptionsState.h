#ifndef GENUS_GMAINOPTIONSSTATE_H
#define GENUS_GMAINOPTIONSSTATE_H

#include <BGameEngine.h>

class GMainOptionsState : public BGameEngine {
public:
  GMainOptionsState();

  virtual ~GMainOptionsState();
private:
    BFont *mFont16, *mFont8;
};

#endif //GENUS_GMAINOPTIONSSTATE_H
