#ifndef GENUS_GNEXTBLOCKSPRITE_H
#define GENUS_GNEXTBLOCKSPRITE_H

#include "GPlayerSprite.h"

class GNextBlockSprite : public GPlayerSprite {
public:
  GNextBlockSprite();

  ~GNextBlockSprite();

public:
  TBool Render(BViewPort *aVP);
};

#endif //GENUS_GNEXTBLOCKSPRITE_H
