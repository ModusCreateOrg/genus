#ifndef GENUS_GCONTINUEWIDGET_H
#define GENUS_GCONTINUEWIDGET_H

#include "Widgets.h"

class GContinueWidget : public BButtonWidget {
public:
    GContinueWidget();
    ~GContinueWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GCONTINUEWIDGET_H
