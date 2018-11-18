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

class GLevelUnderWaterFantasy : public GScrollingLevel {
public:
  GLevelUnderWaterFantasy(GGameState *aGameEngine);
  ~GLevelUnderWaterFantasy();

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
  TFloat mFrame;

  TFloat bgOffset0;
  TFloat bgOffset1;
  TFloat bgOffset2;

  TUint8 mTextColor;
};


#endif //GENUS_GLEVELUNDERWATERFANTASY_H
