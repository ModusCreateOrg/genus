#ifndef GENUS_GGAMEUNDERWATER1_H
#define GENUS_GGAMEUNDERWATER1_H

#include "GameState/GGameState.h"

class GStage2UnderWaterOne : public BPlayfield {
public:
    GStage2UnderWaterOne(GGameState *aGameEngine);
    ~GStage2UnderWaterOne();

public:
    void Animate();
    void Render();
public:
  GGameState *mGameEngine;
  BBitmap *mBackground;
//    TInt8 *mYOffset;
//    TInt8 *mXComp;
  TInt16 mYSinIndex;
  TInt16 mXSinIndex;
  TInt8 *mYOffset;
  TInt8 *mXComp;
  TUint8 mTextColor;
  TFloat mXTimer;
  TFloat mYTimer;
  TFloat mAnimSpeedX;
  TFloat mAnimSpeedY;
};

#endif //GENUS_GGAMEUNDERWATER1_H
