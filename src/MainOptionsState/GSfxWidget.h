#ifndef GENUS_GSFXWIDGET_H
#define GENUS_GSFXWIDGET_H

#include "Widgets.h"

class GSfxWidget : public BSliderWidget {
public:
    GSfxWidget();
    ~GSfxWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aVal);
    void Set(TInt aVal);
};

#endif //GENUS_GSFXWIDGET_H
