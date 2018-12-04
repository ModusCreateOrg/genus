#ifndef GENUS_GRULESWIDGET_H
#define GENUS_GRULESWIDGET_H

#include "Widgets.h"

class GRulesWidget : public BButtonWidget {
public:
    GRulesWidget();
    ~GRulesWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GRULESWIDGET_H
