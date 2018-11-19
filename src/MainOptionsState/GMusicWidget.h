#ifndef GENUS_GMUSICWIDGET_H
#define GENUS_GMUSICWIDGET_H

#include "GSoundSliderWidget.h"

class GMusicWidget : public GSoundSliderWidget {
public:
    GMusicWidget();
    ~GMusicWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aVal);
};

#endif //GENUS_GMUSICWIDGET_H
