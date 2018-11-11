#ifndef GENUS_BPOWERUP_H
#define GENUS_BPOWERUP_H

class GPlayerSprite;

class GGameProcess;

class GGameState;

class GGameBoard;

#include <BProcess.h>
#include "GPlayerSprite.h"

static const TInt REPEAT_TIME  = 1,
                  REPEAT_DELAY = REPEAT_TIME + 2;

class BPowerup : public BProcess {
public:
  BPowerup(GPlayerSprite *aSprite, GGameState *aGameState);

  virtual ~BPowerup();

public:
  TBool TimedControl(TUint16 aButton);

public:
  TBool Move();   // process controls (joystick, buttons)

  void MoveLeft();
  void MoveRight();
  void MoveUp();
  void MoveDown();

  void RotateLeft();
  void RotateRight();

protected:
  GPlayerSprite *mSprite;
  GGameState    *mGameState;
  GGameBoard    *mGameBoard;
  static TInt   mRepeatTimer;
  TBool         mDropped;
  TInt          mState;
};

#endif //GENUS_BPOWERUP_H
