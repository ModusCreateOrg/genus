#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

#include "Game.h"

class GGameState : public BPlayfield {
public:
  GGameState(GGameEngine *aGameEngine);
  virtual ~GGameState();
public:
  void Render();
  void Animate();
protected:
  BBitmap *mBackground1, *mBackground2;
  BBitmap *mCurrentBackground;
  TInt mAnimationTimer;
};


#endif //GENUS_GGAMESTATE_H
