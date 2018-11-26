#include "Game.h"
#include "GNextBlockSprite.h"

static const TInt BLINK_TIME = 2;

GNextBlockSprite::GNextBlockSprite() : GPlayerSprite() {
  this->flags        = SFLAG_RENDER;
  this->mGameOver    = EFalse;
  Randomize();
}

GNextBlockSprite::~GNextBlockSprite() {}

TBool GNextBlockSprite::Render(BViewPort *aVP) {
  if (mGameOver) {
    return ETrue;
  }

  TInt xx = TInt(round(x));
  TInt yy = TInt(round(y));

  if (flags & SFLAG_RENDER) {
    if (mBlockSize == BLOCKSIZE_2x2) {
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[0], xx, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[1], xx + 16, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[2], xx, yy + 16);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[3], xx + 16, yy + 16);
    }
    else {
      BAnimSprite::Render(aVP);
    }
  }

  return ETrue;
}
