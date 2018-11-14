#ifndef GENUS_GEXITWIDGET_H
#define GENUS_GEXITWIDGET_H

#include "Widgets.h"

class GExitWidget : public BButtonWidget {
public:
    GExitWidget();
    ~GExitWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GEXITWIDGET_H
