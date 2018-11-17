#ifndef GENUS_GSPLASHPLAYFIELD_H
#define GENUS_GSPLASHPLAYFIELD_H

#include "Game.h"

class GSplashPlayfield : public BPlayfield {
public:
  GSplashPlayfield();

  virtual ~GSplashPlayfield();

  void Render();

public:
  BBitmap *mBackground;
};

#endif //GENUS_GSPLASHPLAYFIELD_H
