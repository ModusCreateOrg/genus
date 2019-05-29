#ifndef GENUS_GRESUMEWIDGET_H
#define GENUS_GRESUMEWIDGET_H

#include "Widgets.h"

class GResumeWidget : public BButtonWidget {
public:
    GResumeWidget();
    ~GResumeWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GRESUMEWIDGET_H
