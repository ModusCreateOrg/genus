#ifndef GENUS_GNOPOWERUP_H
#define GENUS_GNOPOWERUP_H

// no powerup - regular 2x2 blocks

#include "BPowerup.h"

class GNoPowerup : public BPowerup {
public:
  GNoPowerup(GPlayerSprite *aSprite, GGameState *aGameState);

  ~GNoPowerup();

protected:
  TBool CanDrop();

  TBool Drop();
  void Blink();

  TBool RunBefore();

  TBool RunAfter() { return ETrue; }

protected:
  TBool TimerState();

  TBool RemoveState();

  TBool MoveState();

protected:
  TInt    mBlinkTimer;
  TInt    mRemoveTimer;
  TInt    mRemoveRow, mRemoveCol;
  TUint32 mRemoveScore;
};


#endif //GENUS_GNOPOWERUP_H
