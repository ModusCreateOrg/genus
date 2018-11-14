#ifndef GENUS_GMODUSBOMBPOWERUP_H
#define GENUS_GMODUSBOMBPOWERUP_H

#include "BPowerup.h"

class GModusBombPowerup : public BPowerup {
public:
  GModusBombPowerup(GPlayerSprite *aSprite, GGameState *aGameState);

  ~GModusBombPowerup();

public:
  TBool RunBefore() { return ETrue; }
  TBool RunAfter();

protected:
  TBool Drop();    // actually drop the sprite on the board
  TBool StateMove();

  TBool StateRemove();

  TBool StateWait();

protected:
  TInt mBombStep;
  TInt mBombTimer;
  TInt mBombRow, mBombCol;
};

#endif //GENUS_GMODUSBOMBPOWERUP_H
