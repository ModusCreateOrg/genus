#ifndef GENUS_GPLAYERSPRITE_H
#define GENUS_GPLAYERSPRITE_H

#include <BAnimSprite.h>

enum {
  BLOCKSIZE_2x2,
  BLOCKSIZE_1x1,
};

class GPlayerSprite : public BAnimSprite {
public:
  GPlayerSprite();

  ~GPlayerSprite();

public:
  TInt BoardRow();

  TInt BoardCol();

public:
  void Randomize();

  void RotateLeft();

  void RotateRight();

  void Animate();

  TBool Render(BViewPort *aVP);

  void Swap(GPlayerSprite *aOther);

  void Copy(GPlayerSprite *aOther);

public:
  TInt   mBlinkTimer, mLassoTimer;
  TUint8 mBlocks[4];
  TInt   mBlockSize;
  TBool  mGameOver;
};

#endif //GENUS_GPLAYERSPRITE_H
