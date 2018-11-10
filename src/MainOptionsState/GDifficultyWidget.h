#ifndef GDIFFICULTYWIDGET_H
#define GDIFFICULTYWIDGET_H

#include "Game.h"
#include "Widgets.h"

class GDifficultyWidget : public BSelectWidget {
public:
    GDifficultyWidget();
    virtual ~GDifficultyWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aIndex);
    void Set(TInt aIndex);
};

#endif
