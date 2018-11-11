#ifndef GENUS_GCOLORSWAPPOWERUP_H
#define GENUS_GCOLORSWAPPOWERUP_H

#include "BPowerup.h"

class GColorSwapPowerup : BPowerup {
public:
  GColorSwapPowerup(GPlayerSprite *aSprite, GGameState *aGameState);

  virtual ~GColorSwapPowerup();

public:
  TBool CanDrop();

  virtual TBool Drop(GGameProcess *aProcess);    // actually drop the sprite on the board
  TBool Run();    // run animation for current frame, explosion, whatever, return false when done
};


#endif //GENUS_GCOLORSWAPPOWERUP_H
