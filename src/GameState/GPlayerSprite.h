#ifndef GENUS_GPLAYERSPRITE_H
#define GENUS_GPLAYERSPRITE_H

#include <BAnimSprite.h>

#define SFLAG_NEXT_BLOCK  (1 << SFLAG_USER_BIT)
#define SFLAG_RULES_BLOCK (2 << SFLAG_USER_BIT)

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

  void ResetOverlappingBlocks();

public:
  TInt   mBlinkTimer, mLassoTimer;
  TUint8 mBlocks[4];
  TBool  mBlocksOverlap[4];
  TInt   mBlockSize;
  TBool  mGameOver;
};

#endif //GENUS_GPLAYERSPRITE_H
