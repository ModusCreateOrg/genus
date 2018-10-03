#ifndef GENUS_GCREDITSSTATE_H
#define GENUS_GCREDITSSTATE_H

#include <BPlayfield.h>
#include "GGameEngine.h"

class GCreditsState : public BPlayfield {
public:
  GCreditsState(GGameEngine *aGameEngine);

  virtual ~GCreditsState();

public:
  void Render();

protected:
  BBitmap *mBackground;
};



#endif //GENUS_GCREDITSSTATE_H
