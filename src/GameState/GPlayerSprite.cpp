#include "Game.h"
#include "GPlayerSprite.h"

static const TInt BLINK_TIME = 2;

/*
 *    _          _                 _   _                ____            _       _
 *   / \   _ __ (_)_ __ ___   __ _| |_(_) ___  _ __    / ___|  ___ _ __(_)_ __ | |_ ___
 *  / _ \ | '_ \| | '_ ` _ \ / _` | __| |/ _ \| '_ \   \___ \ / __| '__| | '_ \| __/ __|
 * / ___ \| | | | | | | | | | (_| | |_| | (_) | | | |    ___) | (__| |  | | |_) | |_\__ \
 * /_/    \_\_| |_|_|_| |_| |_|\__,_|\__|_|\___/|_| |_| |____/ \___|_|  |_| .__/ \__|___/
 *                                                                        |_|
 */

GPlayerSprite::GPlayerSprite() : BAnimSprite(0, PLAYER_SLOT) {
  this->flags        = SFLAG_RENDER;
  this->mGameOver    = EFalse;
  Randomize();
}

GPlayerSprite::~GPlayerSprite() {}

TInt GPlayerSprite::BoardRow() {
  return TInt(y - BOARD_Y) / 16;

}

TInt GPlayerSprite::BoardCol() {
  return TInt(x - BOARD_X) / 16;
}

void GPlayerSprite::Randomize() {
  mBlocks[0] = TUint8(Random() & 1 ? 16 : 0);
  mBlocks[1] = TUint8(Random() & 1 ? 16 : 0);
  mBlocks[2] = TUint8(Random() & 1 ? 16 : 0);
  mBlocks[3] = TUint8(Random() & 1 ? 16 : 0);
  this->mBlockSize = BLOCKSIZE_2x2;
}

void GPlayerSprite::RotateLeft() {
  TUint8 save = mBlocks[0];

  mBlocks[0] = mBlocks[1];
  mBlocks[1] = mBlocks[3];
  mBlocks[3] = mBlocks[2];
  mBlocks[2] = save;
  // TODO: Jay - this should be in the caller of this method
  gSoundPlayer.PlaySound(/*SFX_ROTATE_BLOCK_RIGHT_WAV*/4, 0, EFalse);
}

void GPlayerSprite::RotateRight() {
  TUint8 save = mBlocks[0];

  mBlocks[0] = mBlocks[2];
  mBlocks[2] = mBlocks[3];
  mBlocks[3] = mBlocks[1];
  mBlocks[1] = save;
  // TODO: Jay - this should be in the caller of this method
  gSoundPlayer.PlaySound(/*SFX_ROTATE_BLOCK_LEFT_WAV*/3, 0, EFalse);
}

void GPlayerSprite::Animate() {
  mBlinkTimer--;
  if (mBlinkTimer < 0) {
    mBlinkTimer = BLINK_TIME;
  }
  BAnimSprite::Animate();
}

TBool GPlayerSprite::Render(BViewPort *aVP) {
  if (mGameOver) {
    return ETrue;
  }
  TInt xx = TInt(round(x));
  TInt yy = TInt(round(y));

  if (flags & SFLAG_RENDER) {
    if (mBlockSize == BLOCKSIZE_2x2) {
//      BSprite::DrawSprite(gViewPort, COMMON_SLOT, mPowerupImage, xx, yy);
//    } else {
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[0], xx, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[1], xx + 16, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[2], xx, yy + 16);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, mBlocks[3], xx + 16, yy + 16);
      // frame
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMEL, xx, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMER, xx + 16, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMEL, xx, yy + 16, SFLAG_FLOP);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMER, xx + 16, yy + 16, SFLAG_FLOP);
    }
    else {
      BAnimSprite::Render(aVP);
    }
  }
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

void GPlayerSprite::Copy(GPlayerSprite *aOther) {
  this->mBlocks[0] = aOther->mBlocks[0];
  this->mBlocks[1] = aOther->mBlocks[1];
  this->mBlocks[2] = aOther->mBlocks[2];
  this->mBlocks[3] = aOther->mBlocks[3];
  this->mBlockSize = aOther->mBlockSize;
}

