#ifndef GDIFFICULTY_H
#define GDIFFICULTY_H

#include "Game.h"
#include "Widgets.h"

class GDifficulty : public BSelectWidget {
public:
    GDifficulty();
    virtual ~GDifficulty();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aIndex);
    void Set(TInt aIndex);
};

#endif
