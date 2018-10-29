#ifndef GENUS_GMUSIC_H
#define GENUS_GMUSIC_H

#include "Widgets.h"

class GMusic : public BSelectWidget {
public:
    GMusic();
    ~GMusic();
public:
    TInt Render(TInt aX, TInt aY);
    void Select(TInt aIndex);
};

#endif //GENUS_GMUSIC_H
