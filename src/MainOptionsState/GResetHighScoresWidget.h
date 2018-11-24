#ifndef GENUS_GRESETHIGHSCORESWIDGET_H
#define GENUS_GRESETHIGHSCORESWIDGET_H

#include "Widgets.h"

class GResetHighScoresWidget : public BButtonWidget {
public:
    GResetHighScoresWidget();
    ~GResetHighScoresWidget();
public:
    TInt Render(TInt aX, TInt aY);
    void Select();
};

#endif //GENUS_GRESETHIGHSCORESWIDGET_H
