#ifndef GENUS_GPLAYERSPRITE_H
#define GENUS_GPLAYERSPRITE_H

#include <BSprite.h>

enum {
  POWERUP_TYPE_NONE,
  POWERUP_TYPE_M_BOMB,
  POWERUP_TYPE_COLOR_SWAP,
};

class GPlayerSprite : public BSprite {
public:
  GPlayerSprite();

  ~GPlayerSprite();

public:
  void Randomize();

  void RotateLeft();

  void RotateRight();

  void Animate();

  TBool Render(BViewPort *aVP);

  void Swap(GPlayerSprite *aOther);

  void Copy(GPlayerSprite *aOther);

public:
  TInt   mBlinkTimer;
  TUint8 mBlocks[4];
  TBool  mGameOver;
public:
  TInt mPowerupType;
  TInt mPowerupImage;
};

#endif //GENUS_GPLAYERSPRITE_H
