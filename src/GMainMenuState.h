#ifndef GENUS_GMAINMENUSTATE_H
#define GENUS_GMAINMENUSTATE_H

#include <BPlayfield.h>
#include "GGameEngine.h"

class GMainMenuState : public BPlayfield {
public:
  GMainMenuState(GGameEngine *aGameEngine);

  virtual ~GMainMenuState();

public:
  void Render();

protected:
  BBitmap *mBackground;
};

#endif //GENUS_GMAINMENUSTATE_H
