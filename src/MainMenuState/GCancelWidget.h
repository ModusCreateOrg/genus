#ifndef GENUS_GCancelWidget_H
#define GENUS_GCancelWidget_H

#include "Widgets.h"
#include "GMainMenuProcess.h"

class GCancelWidget : public BButtonWidget {
public:
    GCancelWidget(GMainMenuProcess *aProcess);
    ~GCancelWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
    GMainMenuProcess *mProcess;

};

#endif //GENUS_GCancelWidget_H
