#ifndef GENUS_GPLAYERSPRITE_H
#define GENUS_GPLAYERSPRITE_H

#include <BSprite.h>

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
public:
  TInt   mBlinkTimer;
  TUint8 mBlocks[4];
  TBool  mGameOver;
};

#endif //GENUS_GPLAYERSPRITE_H
