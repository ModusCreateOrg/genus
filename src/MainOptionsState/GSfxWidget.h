#ifndef GENUS_GSFXWIDGET_H
#define GENUS_GSFXWIDGET_H

#include "GSoundSliderWidget.h"

class GSfxWidget : public GSoundSliderWidget {
public:
    GSfxWidget();
    ~GSfxWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aVal);
};

#endif //GENUS_GSFXWIDGET_H
