#ifndef GENUS_GSTARTWIDGET_H
#define GENUS_GSTARTWIDGET_H

#include "GButtonWidget.h"

class GMainMenuProcess;

class GStartWidget : public GButtonWidget {
public:
    GStartWidget(GMainMenuProcess *aProcess);
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
public:
    GMainMenuProcess *mProcess;
};

#endif //GENUS_GSTARTWIDGET_H
