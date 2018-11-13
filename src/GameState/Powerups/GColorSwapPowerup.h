#ifndef GENUS_GCOLORSWAPPOWERUP_H
#define GENUS_GCOLORSWAPPOWERUP_H

#include "BPowerup.h"

class GColorSwapPowerup : public BPowerup {
public:
  GColorSwapPowerup(GPlayerSprite *aSprite, GGameState *aGameState);

  virtual ~GColorSwapPowerup();

public:
  TBool RunBefore() { return ETrue; }

  TBool RunAfter();    // run animation for current frame, explosion, whatever, return false when done
protected:
  TBool Drop();    // actually drop the sprite on the board
  TBool StateMove();

  TBool StateRemove();

protected:
  TInt   mColorSwapTimer;
  // stack of points for flood fill (connected blocks)
  TAny   *mPointStack;
  TUint8 mSwapColor;  // color we are replacing
};


#endif //GENUS_GCOLORSWAPPOWERUP_H
