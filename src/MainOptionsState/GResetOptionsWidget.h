#ifndef GENUS_GRESETOPTIONSWIDGET_H
#define GENUS_GRESETOPTIONSWIDGET_H

#include "Widgets.h"

class GResetOptionsWidget : public BButtonWidget {
public:
    GResetOptionsWidget();
    ~GResetOptionsWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GRESETOPTIONSWIDGET_H
