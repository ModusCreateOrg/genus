#ifndef GENUS_GNOPOWERUP_H
#define GENUS_GNOPOWERUP_H

// no powerup - regular 2x2 blocks

#include "BPowerup.h"

class GNoPowerup : public BPowerup {
public:
  GNoPowerup(GPlayerSprite *aSprite, GGameState *aGameState);
  ~GNoPowerup();
public:
  TBool CanDrop();
  TBool Drop(GGameProcess *aProcess);
  TBool Run();
protected:
  TInt mRemoveTimer;
  TInt mRemoveRow, mRemoveCol;
  TUint32 mRemoveScore;
};


#endif //GENUS_GNOPOWERUP_H
