#ifndef GENUS_GMUSICWIDGET_H
#define GENUS_GMUSICWIDGET_H

#include "Widgets.h"

class GMusicWidget : public BSliderWidget {
public:
    GMusicWidget();
    ~GMusicWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aVal);
    void Set(TInt aVal);
};

#endif //GENUS_GMUSICWIDGET_H
