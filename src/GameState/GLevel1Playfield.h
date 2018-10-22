#ifndef GENUS_GGAMEPLAYFIELD_H
#define GENUS_GGAMEPLAYFIELD_H

#include "GGameState.h"

class GLevel1Playfield : public BPlayfield {
public:
    GLevel1Playfield(GGameState *aGameEngine);
    ~GLevel1Playfield();

public:
    void Animate();
    void Render();
public:
    GGameState *mGameEngine;
    BBitmap *mBackground;
    TUint8 mTextColor;
};

#endif //GENUS_GGAMEPLAYFIELD_H
