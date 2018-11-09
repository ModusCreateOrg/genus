#ifndef GENUS_GMODUSBOMBPOWERUP_H
#define GENUS_GMODUSBOMBPOWERUP_H

#include "BPowerup.h"

class GModusBombPowerup : public BPowerup {
public:
  GModusBombPowerup(GPlayerSprite *aSprite, GGameState *aGameState);

  virtual ~GModusBombPowerup();

public:
  TBool CanDrop();    // return true if sprite can be dropped on the board
  virtual TBool Drop(GGameProcess *aProcess);    // actually drop the sprite on the board
  TBool Run();    // run animation for current frame, explosion, whatever, return false when done
protected:
  TInt mBombStep;
  TInt mBombTimer;
  TInt mBombRow, mBombCol;
//  TUint32 mRemoveScore;
};

#endif //GENUS_GMODUSBOMBPOWERUP_H
