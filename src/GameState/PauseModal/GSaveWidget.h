#ifndef GENUS_GSAVEWIDGET_H
#define GENUS_GSAVEWIDGET_H

#include "Widgets.h"

class GSaveWidget : public BButtonWidget {
public:
    GSaveWidget();
    ~GSaveWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GSAVEWIDGET_H
