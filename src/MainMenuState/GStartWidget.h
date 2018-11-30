#ifndef GENUS_GSTARTWIDGET_H
#define GENUS_GSTARTWIDGET_H

#include "Widgets.h"

class GStartWidget : public BButtonWidget {
public:
    GStartWidget();
    ~GStartWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GSTARTWIDGET_H
