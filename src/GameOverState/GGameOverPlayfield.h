#ifndef GENUS_GGAMEOVERPLAYFIELD_H
#define GENUS_GGAMEOVERPLAYFIELD_H

#include "Game.h"

class GGameOverPlayfield : public BPlayfield {
public:
  GGameOverPlayfield();
  virtual ~GGameOverPlayfield();

public:
  void Render();

public:
  BBitmap *mBackground;
};


#endif //GENUS_GGAMEOVERPLAYFIELD_H
