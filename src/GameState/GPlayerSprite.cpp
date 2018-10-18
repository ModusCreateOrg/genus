#include "Game.h"
#include "GPlayerSprite.h"

static const TInt BLINK_TIME   = 2;

GPlayerSprite::GPlayerSprite() : BSprite(0, PLAYER_SLOT) {
  this->flags     = SFLAG_RENDER;
  this->mGameOver = EFalse;
  Randomize();
}

GPlayerSprite::~GPlayerSprite() {}


void GPlayerSprite::Randomize() {
  mBlocks[0] = TUint8(Random() & 1);
  mBlocks[1] = TUint8(Random() & 1);
  mBlocks[2] = TUint8(Random() & 1);
  mBlocks[3] = TUint8(Random() & 1);
  this->x  = PLAYER_X;
  this->y  = PLAYER_Y;
  this->vy = 0;
}

void GPlayerSprite::RotateLeft() {
  TUint8 save = mBlocks[0];

  mBlocks[0] = mBlocks[1];
  mBlocks[1] = mBlocks[3];
  mBlocks[3] = mBlocks[2];
  mBlocks[2] = save;
}

void GPlayerSprite::RotateRight() {
  TUint8 save = mBlocks[0];

  mBlocks[0] = mBlocks[2];
  mBlocks[2] = mBlocks[3];
  mBlocks[3] = mBlocks[1];
  mBlocks[1] = save;
}

void GPlayerSprite::Animate() {
  mBlinkTimer--;
  if (mBlinkTimer < 0) {
    mBlinkTimer = BLINK_TIME;
  }
}

TBool GPlayerSprite::Render(BViewPort *aVP) {
  if (mGameOver) {
    return ETrue;
  }
  BBitmap *bm = gDisplay.renderBitmap;
  TInt    xx  = TInt(x + .5);
  TInt    yy  = TInt(y + .5);

  if (flags & SFLAG_RENDER) {
    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[0], xx, yy);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[1], xx + 16, yy);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[2], xx, yy + 16);
    bm->DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[3], xx + 16, yy + 16);
  }
  // frame
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMEL, xx, yy);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMER, xx + 16, yy);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMEL, xx, yy + 16, SFLAG_FLOP);
  bm->DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMER, xx + 16, yy + 16, SFLAG_FLOP);
  return ETrue;
}

void GPlayerSprite::Swap(GPlayerSprite *aOther) {
  TUint8 save;

  save = aOther->mBlocks[0];
  aOther->mBlocks[0] = this->mBlocks[0];
  this->mBlocks[0]   = save;

  save = aOther->mBlocks[1];
  aOther->mBlocks[1] = this->mBlocks[1];
  this->mBlocks[1]   = save;

  save = aOther->mBlocks[2];
  aOther->mBlocks[2] = this->mBlocks[2];
  this->mBlocks[2]   = save;

  save = aOther->mBlocks[3];
  aOther->mBlocks[3] = this->mBlocks[3];
  this->mBlocks[3]   = save;
}

