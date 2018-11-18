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
  void MoveLeft();

  void MoveRight();

  void MoveUp();

  void MoveDown();

  void RotateLeft();

  void RotateRight();

protected:
  GPlayerSprite *mPlayerSprite;
  GGameState    *mGameState;
  GGameBoard    *mGameBoard;
  static TInt   mRepeatTimer;
  // powerups and no-powerup have these 4 states
  enum {
    STATE_MOVE,   // move/control the powerup/2x2
    STATE_TIMER,  // timer is running, move the no-power
    STATE_REMOVE, // process is removing blocks from board
    STATE_WAIT,   // process is waiting (do nothing)
  }             mState;
};

#endif //GENUS_BPOWERUP_H
