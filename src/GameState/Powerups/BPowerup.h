#ifndef GENUS_BPOWERUP_H
#define GENUS_BPOWERUP_H

class GPlayerSprite;

class GGameProcess;

class GGameState;

class GGameBoard;

#include <BBase.h>
#include "GPlayerSprite.h"

class BPowerup : public BBase {
public:
  BPowerup(GPlayerSprite *aSprite, GGameState *aGameState);
  virtual ~BPowerup();

public:
  TBool TimedControl(TUint16 aButton);

public:
  TBool Move();   // process controls (joystick, buttons)

public:
  // return true if sprite can be dropped on the board
  virtual TBool CanDrop() = 0;

  // returns ETrue if drop added to or created at least one 2x2 same blocks
  virtual TBool Drop(GGameProcess *aProcess) = 0;    // actually drop the sprite on the board

  // run animation for current frame, explosion, whatever, return false when done
  virtual TBool Run() = 0;


protected:
  GPlayerSprite *mSprite;
  GGameState    *mGameState;
  GGameBoard    *mGameBoard;
  static TInt   mRepeatTimer;
  TBool         mDropped;
};

#endif //GENUS_BPOWERUP_H
