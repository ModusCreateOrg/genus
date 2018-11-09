#ifndef GENUS_GMUSIC_H
#define GENUS_GMUSIC_H

#include "Widgets.h"

class GMusic : public BSliderWidget {
public:
    GMusic();
    ~GMusic();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aVal);
    void Set(TInt aVal);
};

#endif //GENUS_GMUSIC_H
