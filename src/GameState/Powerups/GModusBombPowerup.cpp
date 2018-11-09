#include "GModusBombPowerup.h"
#include "GGameState.h"
#include "Game.h"

ANIMSCRIPT BombAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP1(IMG_POWERUP_MODUS),
  ASTEP1(IMG_POWERUP_MODUS + 1),
  ALOOP
};

GModusBombPowerup::GModusBombPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : BPowerup(aSprite, aGameState) {
  mSprite->mBlockSize = BLOCKSIZE_1x1;
  mSprite->StartAnimation(BombAnimation);
}

GModusBombPowerup::~GModusBombPowerup() {

}

TBool GModusBombPowerup::CanDrop() {
  return ETrue; // bomb can be dropped anywhere
}

TBool GModusBombPowerup::Drop(GGameProcess *aProcess) {
  // disable rendering
  mSprite->flags &= ~SFLAG_RENDER;

  // notify GameState that blocks are being removed
  mGameState->mBlocksRemoving = ETrue;

  // where on the board the bomb was placed
  mBombRow = mSprite->BoardRow();
  mBombCol = mSprite->BoardCol();

  mBombStep  = 0;  // animation step
  mBombTimer = 1; // 1st step immediately
  mDropped   = ETrue;

  return EFalse;
}

TBool GModusBombPowerup::Run() {
  if (!mDropped) {
    return ETrue;
  }
  if (mBombTimer--) {
    return ETrue;
  }
  mBombTimer = 30 / 2;        // 1/8 second

  TInt row = mBombRow,
       col = mBombCol;

  switch (mBombStep++) {
    case 0:
      mGameBoard->ExplodeBlock(row, col);
      return ETrue;
    case 1:
      mGameBoard->ExplodeBlock(row - 1, col - 1);
      mGameBoard->ExplodeBlock(row - 1, col);
      mGameBoard->ExplodeBlock(row - 1, col + 1);
      mGameBoard->ExplodeBlock(row, col - 1);
      mGameBoard->ExplodeBlock(row, col + 1);
      mGameBoard->ExplodeBlock(row + 1, col - 1);
      mGameBoard->ExplodeBlock(row + 1, col);
      mGameBoard->ExplodeBlock(row + 1, col + 1);
      return ETrue;
    case 3:
      mGameBoard->ExplodeBlock(row - 2, col);
      mGameBoard->ExplodeBlock(row, col - 2);
      mGameBoard->ExplodeBlock(row, col + 2);
      mGameBoard->ExplodeBlock(row + 2, col);
      return ETrue;
    default:
      // done!
      mSprite->flags |= SFLAG_RENDER;
      gControls.dKeys             = 0;  // in case user pressed a key during removing blocks
      mGameState->mBlocksRemoving = EFalse;
      return EFalse;
  }
}