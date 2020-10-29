#ifndef GENUS_GLEVELUNDERWATERFANTASY_H
#define GENUS_GLEVELUNDERWATERFANTASY_H

#include "GGameState.h"
#include "Playfields/GScrollingLevel.h"
#include "BViewPort.h"



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


  TInt8 *mYOffset;
  TInt8 *mXComp;
  TInt16 mYSinIndex;
  TInt16 mXSinIndex;
  TFloat mXTimer;
  TFloat mYTimer;
  TFloat mAnimSpeedX;
  TFloat mAnimSpeedY;
  TUint8 mTextColor;
};


#endif //GENUS_GLEVELUNDERWATERFANTASY_H
