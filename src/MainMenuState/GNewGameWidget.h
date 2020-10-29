#ifndef GENUS_GNEWGAMEWIDGET_H
#define GENUS_GNEWGAMEWIDGET_H

#include "Widgets.h"

class GNewGameWidget : public BButtonWidget {
public:
    GNewGameWidget();
    ~GNewGameWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GNEWGAMEWIDGET_H
