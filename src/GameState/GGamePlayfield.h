#ifndef GENUS_GGAMEPLAYFIELD_H
#define GENUS_GGAMEPLAYFIELD_H

#include "GGameState.h"

class GGamePlayfield : public BPlayfield {
public:
    GGamePlayfield(GGameState *aGameEngine);
    ~GGamePlayfield() {

    }

public:
    void Animate();
    void Render();
public:
    GGameState *mGameEngine;
    BBitmap *mBackground;
    TUint8 mTextColor;
};

#endif //GENUS_GGAMEPLAYFIELD_H
