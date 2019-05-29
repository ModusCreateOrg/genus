#ifndef GENUS_GRESTARTWIDGET_H
#define GENUS_GRESTARTWIDGET_H

#include "Widgets.h"

class GRestartWidget : public BButtonWidget {
public:
    GRestartWidget();
    ~GRestartWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GRESTARTWIDGET_H
