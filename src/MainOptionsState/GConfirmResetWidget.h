#ifndef GENUS_GCONFIRMRESETWIDGET_H
#define GENUS_GCONFIRMRESETWIDGET_H

#include "Widgets.h"

class GConfirmResetWidget : public BButtonWidget {
public:
    GConfirmResetWidget();
    ~GConfirmResetWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GCONFIRMRESETWIDGET_H
