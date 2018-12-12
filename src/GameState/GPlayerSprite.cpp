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
  this->flags        |= SFLAG_RENDER;
  this->mGameOver    = EFalse;
  this->mBlinkTimer  = BLINK_TIME;
  Randomize();
  ResetOverlappingBlocks();
}

GPlayerSprite::~GPlayerSprite() {}

void GPlayerSprite::ResetOverlappingBlocks() {
  memset(mBlocksOverlap, EFalse, sizeof(mBlocksOverlap));
}

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
  mLassoTimer++;
//    gDisplay.renderBitmap->SetColor(LASSO_1, 255,255,255);
//    gDisplay.renderBitmap->SetColor(LASSO_2, 255,255,255);
//  if (mLassoTimer & 8) {
//    gDisplay.renderBitmap->SetColor(LASSO_1, 255,255,255);
//    gDisplay.renderBitmap->SetColor(LASSO_2, 255,0,255);
//  }
//  else {
//    gDisplay.renderBitmap->SetColor(LASSO_1, 255,0,255);
//    gDisplay.renderBitmap->SetColor(LASSO_2, 255,255,255);
//  }
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
      TInt8 blocks[4];

      // On HARD difficulty we show a filled NEXT block to the player
      if (gOptions->difficulty == DIFFICULTY_HARD && (flags & SFLAG_NEXT_BLOCK)) {
        memset(blocks, 0, sizeof(blocks));
      } else {
        memcpy(blocks, mBlocks, sizeof(mBlocks));

        if (mBlocksOverlap[0]) {
          blocks[0] = blocks[0] == 0 ? 22 : 23;
        }

        if (mBlocksOverlap[1]) {
          blocks[1] = blocks[1] == 0 ? 22 : 23;
        }

        if (mBlocksOverlap[2]) {
          blocks[2] = blocks[2] == 0 ? 22 : 23;
        }

        if (mBlocksOverlap[3]) {
          blocks[3] = blocks[3] == 0 ? 22 : 23;
        }
      }

      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, blocks[0], xx, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, blocks[1], xx + 16, yy);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, blocks[2], xx, yy + 16);
      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, blocks[3], xx + 16, yy + 16);

      // frame
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMEL, xx, yy);
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMER, xx + 16, yy);
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMEL, xx, yy + 16, SFLAG_FLOP);
//      BSprite::DrawSprite(gViewPort, PLAYER_SLOT, IMG_FRAMER, xx + 16, yy + 16, SFLAG_FLOP);

      if (!(flags & (SFLAG_NEXT_BLOCK | SFLAG_RULES_BLOCK))) {
        BBitmap *bm = gDisplay.renderBitmap;
        TInt linesColor = COLOR_BORDER1;
        TInt maxBoardX = BOARD_COLS * 16;
        TInt maxBoardY = BOARD_ROWS * 16;

        bm->DrawFastHLine(gViewPort, BOARD_X, yy - 1, maxBoardX, linesColor);
        bm->DrawFastHLine(gViewPort, BOARD_X, yy + 32, maxBoardX, linesColor);

        bm->DrawFastVLine(gViewPort, xx - 1, BOARD_Y, maxBoardY, linesColor);
        bm->DrawFastVLine(gViewPort, xx + 32, BOARD_Y, maxBoardY, linesColor);
      }

      if (!(flags & SFLAG_NEXT_BLOCK)) {
        TInt animationFrame = mLassoTimer & 8 ? 4 : 0;
        gDisplay.renderBitmap->SetColor(LASSO_1, 255,255,255);
        BSprite::DrawSprite(gViewPort, COMMON_SLOT, IMG_LASSO_UL + animationFrame, xx, yy);
        BSprite::DrawSprite(gViewPort, COMMON_SLOT, IMG_LASSO_UR + animationFrame, xx + 16, yy);
        BSprite::DrawSprite(gViewPort, COMMON_SLOT, IMG_LASSO_LL + animationFrame, xx, yy + 16);
        BSprite::DrawSprite(gViewPort, COMMON_SLOT, IMG_LASSO_LR + animationFrame, xx + 16, yy + 16);
      }
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

