#ifndef GENUS_GRESETWIDGET_H
#define GENUS_GRESETWIDGET_H

#include "Widgets.h"

class GResetWidget : public BButtonWidget {
public:
    GResetWidget();
    ~GResetWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GRESETWIDGET_H
