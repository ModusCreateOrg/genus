#ifndef GENUS_GCREDITSWIDGET_H
#define GENUS_GCREDITSWIDGET_H

#include "Widgets.h"

class GCreditsWidget : public BButtonWidget {
public:
    GCreditsWidget();
    ~GCreditsWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GCREDITSWIDGET_H
