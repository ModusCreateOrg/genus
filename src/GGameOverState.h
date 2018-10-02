#ifndef GENUS_GGAMEOVERSTATE_H
#define GENUS_GGAMEOVERSTATE_H


#include <BPlayfield.h>
#include "GGameEngine.h"

class GGameOverState : public BPlayfield {
public:
  GGameOverState(GGameEngine *aGameEngine);

  virtual ~GGameOverState();

public:
  void Render();

protected:
  BBitmap *mBackground;
};


#endif //GENUS_GGAMEOVERSTATE_H
