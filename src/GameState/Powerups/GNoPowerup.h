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

  TBool RunBefore() { return ETrue; }

  TBool RunAfter();

public:
  // tell process to sleep until signaled
  void Wait();
  // tell process to wake up
  void Signal();
protected:
  TBool TimerState();

  TBool RemoveState();

  TBool MoveState();

  TBool WaitState();

protected:
  TInt    mBlinkTimer;
  TInt    mRemoveTimer;
  TInt    mRemoveRow, mRemoveCol;
  TUint32 mRemoveScore;
};


#endif //GENUS_GNOPOWERUP_H
