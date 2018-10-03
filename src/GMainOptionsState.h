#ifndef GENUS_GMAINOPTIONSSTATE_H
#define GENUS_GMAINOPTIONSSTATE_H

#include <BPlayfield.h>
#include "GGameEngine.h"

class GMainOptionsState : public BPlayfield {
public:
  GMainOptionsState(GGameEngine *aGameEngine);

  virtual ~GMainOptionsState();

public:
  void Render();

protected:
  BBitmap *mBackground;
};

#endif //GENUS_GMAINOPTIONSSTATE_H
