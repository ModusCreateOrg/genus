#ifndef GENUS_GOPTIONSWIDGET_H
#define GENUS_GOPTIONSWIDGET_H

#include "Widgets.h"

class GOptionsWidget : public BButtonWidget {
public:
    GOptionsWidget();
    ~GOptionsWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GOPTIONSWIDGET_H
