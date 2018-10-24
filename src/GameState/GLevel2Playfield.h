//
// Created by Jesus Garcia on 10/23/18.
//

#ifndef GENUS_GLEVEL2PLAYFIELD_H
#define GENUS_GLEVEL2PLAYFIELD_H

#include "GGameState.h"
class GLevel2Playfield : public BPlayfield {
public:
  GLevel2Playfield(GGameState *aGameEngine);
  ~GLevel2Playfield();

public:
  void Animate();
  void Render();
public:
  GGameState *mGameEngine;
  BBitmap *mBackground0;
  BBitmap *mBackground1;
  BBitmap *mBackground2;

  float bgOffset0;
  float bgOffset1;
  float bgOffset2;

  TInt64 mFrame;
  TUint8 mTextColor;
};


#endif //GENUS_GLEVEL2PLAYFIELD_H

