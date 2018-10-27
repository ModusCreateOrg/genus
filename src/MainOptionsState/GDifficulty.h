#ifndef GDIFFICULTY_H
#define GDIFFICULTY_H

#include "Game.h"
#include "Widgets.h"

class GDifficulty : public BSelectWidget {
public:
    GDifficulty();
    virtual ~GDifficulty();
    TInt Render(TInt aX, TInt aY);
public:
    void Select(TInt aIndex);
};

#endif

