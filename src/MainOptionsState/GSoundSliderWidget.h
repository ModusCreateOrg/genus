#ifndef GENUS_GSOUNDSLIDERWIDGET_H
#define GENUS_GSOUNDSLIDERWIDGET_H

#include "Widgets.h"

class GSoundSliderWidget : public BSliderWidget {
public:
    GSoundSliderWidget(char *aTitle, const TRange *aRange, TInt aForeground, TInt aBackground = -1);

    GSoundSliderWidget(const char *aTitle, const TRange *aRange, TInt aForeground, TInt aBackground = -1);
    ~GSoundSliderWidget();
public:
    TInt Render(TInt aX, TInt aY);
    TInt RenderTitle(TInt aX, TInt aY, TBool aActive = EFalse);
    void Set(TInt aVal);
    virtual void Select(TInt aVal) = 0;
};

#endif //GENUS_GSOUNDSLIDERWIDGET_H
