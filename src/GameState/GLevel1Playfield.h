//
// Created by Jesus Garcia on 10/23/18.
//

#ifndef GENUS_GLevel1PLAYFIELD_H
#define GENUS_GLevel1PLAYFIELD_H

#include "GGameState.h"
class GLevel1Playfield : public BPlayfield {
public:
  GLevel1Playfield(GGameState *aGameEngine);
  ~GLevel1Playfield();


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

  TUint8 mTextColor;
private:
  void DrawScrolledBackgroundWithTransparency(BBitmap *aBitmap, TFloat aBackgroundOffsetH, TUint aVerticalOffset);
  void DrawScrolledBackground(BBitmap *aBitmap, TFloat aBackgroundOffsetH, TUint aVerticalOffset);

};


#endif //GENUS_GLevel1PLAYFIELD_H

