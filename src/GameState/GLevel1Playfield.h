//
// Created by Jesus Garcia on 10/23/18.
//

#ifndef GENUS_GLevel1PLAYFIELD_H
#define GENUS_GLevel1PLAYFIELD_H

#include "GGameState.h"
#include "GScrollingLevel.h"

class GLevel1Playfield : public GScrollingLevel {
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
    BBitmap *mBackground3;
    BBitmap *mBackground4;
    BBitmap *mBackground5;

    float bgOffset0;
    float bgOffset1;
    float bgOffset2;
    float bgOffset3;
    float bgOffset4;
    float bgOffset5;

    TUint8 mTextColor;
};


#endif //GENUS_GLevel1PLAYFIELD_H

