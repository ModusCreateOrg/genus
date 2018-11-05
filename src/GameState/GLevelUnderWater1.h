#ifndef GENUS_GGAMEUNDERWATER1_H
#define GENUS_GGAMEUNDERWATER1_H

#include "GGameState.h"

class GLevelUnderWater1 : public BPlayfield {
public:
    GLevelUnderWater1(GGameState *aGameEngine);
    ~GLevelUnderWater1();

public:
    void Animate();
    void Render();
public:
  GGameState *mGameEngine;
  BBitmap *mBackground;
//    TInt8 *mYOffset;
//    TInt8 *mXComp;
  int8_t *mYOffset;
  int8_t *mXComp;
  TInt64 mFrame;
  TUint8 mTextColor;
};

#endif //GENUS_GGAMEUNDERWATER1_H
