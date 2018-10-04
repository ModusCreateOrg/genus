#ifndef GENUS_GSPLASH_H
#define GENUS_GSPLASH_H

#include <BPlayfield.h>
#include "GGameEngine.h"

class GSplashState : public BPlayfield {
public:
  GSplashState(GGameEngine *aGameEngine);

  virtual ~GSplashState();

public:
  void Render();

protected:
  BBitmap *mBakcground;
};


#endif //GENUS_GSPLASH_H
