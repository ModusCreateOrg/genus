#ifndef GENUS_GBUTTONWIDGET_H
#define GENUS_GBUTTONWIDGET_H

#include <Widgets/BButtonWidget.h>

class GButtonWidget : public BButtonWidget {
public:
    EXPLICIT GButtonWidget(const char *aText, TInt aState = -1);

    TInt Render(TInt aX, TInt aY) OVERRIDE;
    void Select() OVERRIDE;

    TInt mState;
};

#endif //GENUS_GBUTTONWIDGET_H
