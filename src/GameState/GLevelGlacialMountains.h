//
// Created by Jesus Garcia on 11/5/18.
//

#ifndef GENUS_GLEVELGLACIALMOUNTAINS_H
#define GENUS_GLEVELGLACIALMOUNTAINS_H

#include "GGameState.h"
#include "GScrollingLevel.h"

class GLevelGlacialMountains : public GScrollingLevel {
public:
  GLevelGlacialMountains(GGameState *aGameEngine);
  ~GLevelGlacialMountains();

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
