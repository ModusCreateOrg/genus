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
  int mYSinIndex;
  int mXSinIndex;
  int8_t *mYOffset;
  int8_t *mXComp;
  TUint8 mTextColor;
};

#endif //GENUS_GGAMEUNDERWATER1_H
