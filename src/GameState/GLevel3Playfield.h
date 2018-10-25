#ifndef GENUS_GGAMEPLAYFIELD_H
#define GENUS_GGAMEPLAYFIELD_H

#include "GGameState.h"

class GLevel3Playfield : public BPlayfield {
public:
    GLevel3Playfield(GGameState *aGameEngine);
    ~GLevel3Playfield();

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

#endif //GENUS_GGAMEPLAYFIELD_H
