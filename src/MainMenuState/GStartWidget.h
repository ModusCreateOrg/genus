#ifndef GENUS_GSTARTWIDGET_H
#define GENUS_GSTARTWIDGET_H

#include "Widgets.h"

class GMainMenuProcess;

class GStartWidget : public BButtonWidget {
public:
    GStartWidget(GMainMenuProcess *aProcess);
    ~GStartWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
public:
    GMainMenuProcess *mProcess;
};

#endif //GENUS_GSTARTWIDGET_H
