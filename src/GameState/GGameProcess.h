#ifndef GENUS_GGAMEPROCESS_H
#define GENUS_GGAMEPROCESS_H

#include <BProcess.h>
#include "GGameBoard.h"
#include "GPlayerSprite.h"
#include "Powerups/Powerups.h"

class GGameState;

class GGameProcess : public BProcess {
public:
  GGameProcess(GGameState *aGameState);

  virtual ~GGameProcess();

public:
  TBool TimedControl(TUint16 aButton);

protected:
  // Drop methods for the powerups and normal
  void Drop2x2();

  void DropMBomb();

public:
  TBool CanDrop();

  TBool Drop();

  void MaybePowerup();

protected:
  TBool StateGameOver();

  TBool StatePlay();

  TBool StateRemoveBlocks();

protected:
  TInt mBombStep;

  TBool StateMBomb();

public:
  void RemoveBlocks();

public:
  TBool RunBefore();

  TBool RunAfter();

public:
  BPowerup *mPowerup;
  TInt     mState;
  TInt     mRepeatTimer;
  TInt     mBlinkTimer;
public:
  GPlayerSprite *mSprite;
  GPlayerSprite *mNextSprite;
  GGameState    *mGameState;
  GGameBoard    *mGameBoard;
public:
#if 0
  TInt    mRemoveRow, mRemoveCol;
  TInt    mRemoveTimer;
  TUint32 mRemoveScore;
#endif
};

#endif //GENUS_GGAMEPROCESS_H
