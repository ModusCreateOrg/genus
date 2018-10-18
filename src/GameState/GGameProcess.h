#ifndef GENUS_GGAMEPROCESS_H
#define GENUS_GGAMEPROCESS_H

#include <BProcess.h>
//#include "GGameState.h"
#include "GPlayerSprite.h"

class GGameState;

class GGameProcess : public BProcess {
public:
  GGameProcess(GGameState *aGameState);

  virtual ~GGameProcess();

  TInt BoardRow();

  TInt BoardCol();

  TBool CanDrop();

  TBool Drop();

  TBool StateGameOver();

  TBool TimedControl(TUint16 aButton);

  void StateControl();

  TBool RunBefore();

  TBool RunAfter();

public:
  TInt          mState;
  TInt          mRepeatTimer;
  TInt          mBlinkTimer;
  GPlayerSprite *mSprite;
  GGameState    *mGameState;
  GPlayerSprite *mNextSprite1;
  GPlayerSprite *mNextSprite2;
};

#endif //GENUS_GGAMEPROCESS_H
