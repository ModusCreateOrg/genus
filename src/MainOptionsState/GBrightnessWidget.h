#ifndef GENUS_GBRIGHTNESSWIDGET_H
#define GENUS_GBRIGHTNESSWIDGET_H

#include "GSoundSliderWidget.h"

class GBrightnessWidget : public GSoundSliderWidget {
public:
    GBrightnessWidget();
    ~GBrightnessWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aVal);
};

#endif //GENUS_GBRIGHTNESSWIDGET_H
