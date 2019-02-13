//
// Created by Jesus Garcia on 11/5/18.
//

#ifndef GENUS_GLEVELUNDERWATERFANTASY_H
#define GENUS_GLEVELUNDERWATERFANTASY_H

#include "GGameState.h"
#include "Playfields/GScrollingLevel.h"
#include "BViewPort.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif

class GStage4UnderWaterFantasy : public GScrollingLevel {
public:
  GStage4UnderWaterFantasy(GGameState *aGameEngine);
  ~GStage4UnderWaterFantasy();

  void Animate();
  void Render();


public:
  GGameState *mGameEngine;

  BViewPort *mViewport;
  BBitmap *mCanvasBitmap;
  BBitmap *mBackground0;
  BBitmap *mBackground1;
  BBitmap *mBackground2;
  void DrawScrolledBackground(BBitmap *aBitmap, TFloat aOffsetX, TUint aVerticalOffset, TBool aDrawTransparent, BBitmap *aTargetBitmap);


  int8_t *mYOffset;
  int8_t *mXComp;
  int mYSinIndex;
  int mXSinIndex;

  TUint8 mTextColor;
};


#endif //GENUS_GLEVELUNDERWATERFANTASY_H
