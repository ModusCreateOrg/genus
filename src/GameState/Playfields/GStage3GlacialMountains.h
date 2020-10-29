#ifndef GENUS_GLEVELGLACIALMOUNTAINS_H
#define GENUS_GLEVELGLACIALMOUNTAINS_H

#include "GameState/GGameState.h"
#include "GScrollingLevel.h"

class GStage3GlacialMountains : public GScrollingLevel {
public:
  GStage3GlacialMountains(GGameState *aGameEngine);
  ~GStage3GlacialMountains();

  void Animate();
  void Render();


public:
  GGameState *mGameEngine;
  TUint8 mTextColor;
  BBitmap *mBackground0;

#ifndef STATIC_GAME_BACKGROUNDS

  BBitmap *mBackground1;
  BBitmap *mBackground2;
  BBitmap *mBackground3;
  BBitmap *mBackground4;
  BBitmap *mBackground5;

  float bgOffset0;
  float bgOffset1;
  float bgOffset2;
  float bgOffset3;
  float bgOffset4;
  float bgOffset5;
#endif
};




#endif //GENUS_GLEVELGLACIALMOUNTAINS_H
