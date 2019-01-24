#ifndef GENUS_GRESETALLWIDGET_H
#define GENUS_GRESETALLWIDGET_H

#include "Widgets.h"

class GResetAllWidget : public BButtonWidget {
public:
    GResetAllWidget();
    ~GResetAllWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GRESETALLWIDGET_H
