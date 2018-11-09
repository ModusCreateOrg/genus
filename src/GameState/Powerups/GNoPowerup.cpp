#include "GNoPowerup.h"
#include "GGameState.h"

GNoPowerup::GNoPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : BPowerup(aSprite, aGameState) {
  mSprite->mBlockSize = BLOCKSIZE_2x2;
}

GNoPowerup::~GNoPowerup() {

}

TBool GNoPowerup::CanDrop() {
  TInt row = mSprite->BoardRow(),
       col = mSprite->BoardCol();

  if (mGameBoard->mBoard[row][col] != 255 || mGameBoard->mBoard[row][col + 1] != 255 ||
      mGameBoard->mBoard[row + 1][col] != 255 || mGameBoard->mBoard[row + 1][col + 1] != 255) {
    return EFalse;
  }
  return ETrue;
}

TBool GNoPowerup::Drop(GGameProcess *aProcess) {
  const TInt   row = mSprite->BoardRow(),
               col = mSprite->BoardCol();
  const TUint8 *b  = mSprite->mBlocks;

  TUint8 (*p)[BOARD_ROWS][BOARD_COLS] = &mGameBoard->mBoard;
  (*p)[row][col]         = b[0];
  (*p)[row][col + 1]     = b[1];
  (*p)[row + 1][col]     = b[2];
  (*p)[row + 1][col + 1] = b[3];

  mDropped = ETrue;


  TBool ret = mGameBoard->Combine();
#if 0
  if (!ret && mGameState->mBonusTimer < 0) {
    printf("bonus timer: %d\n", mGameState->mBonusTimer);
    mSprite->MaybePowerup();
  }
#endif
//  if (!ret && mGameState->mBonusTimer < 0) {
//    mRemoveRow                  = mRemoveCol = 0;
//    mRemoveScore                = 1;
//    mRemoveTimer                = 1;
//    mSprite->flags &= ~SFLAG_RENDER;
//    mGameState->mBlocksRemoving = ETrue;
//  }
  return ret;
}

TBool GNoPowerup::Run() {
  if (!mDropped) {
    if (mGameState->mBonusTimer >= 0) {
      mGameState->mBonusTimer--;
      if (mGameState->mBonusTimer < 0) {
        printf("timer exausted\n");
        mRemoveRow                  = mRemoveCol = 0;
        mRemoveScore                = 1;
        mRemoveTimer                = 1;
        mSprite->flags &= ~SFLAG_RENDER;
        mGameState->mBlocksRemoving = ETrue;
      }
    }
    return ETrue;
  }
  if (mRemoveTimer--) {
    return ETrue;
  }
  mRemoveTimer = 30 / 8;        // 1/8 second

  while (mRemoveRow < BOARD_ROWS) {
    if (mRemoveCol >= BOARD_COLS) {
      mRemoveCol = 0;
      mRemoveRow++;
      if (mRemoveRow >= BOARD_ROWS) {
        // all done, game resumes
        mGameState->mBlocksRemoving = EFalse;
        mSprite->flags |= SFLAG_RENDER;
        gControls.dKeys             = 0;  // in case user pressed a key during removing blocks
        return EFalse;
      }
    }
    TUint8 v = mGameBoard->mBoard[mRemoveRow][mRemoveCol];
    if (v != 255) {
      if ((v > 0 && v <= 5) || (v > 16 && v <= 21)) {
        TBCD add;
        add.FromUint32(mRemoveScore);
        mGameState->mScore.Add(add);
        mRemoveScore++;
        // remove the block - start explosion
        mGameBoard->ExplodeBlock(mRemoveRow, mRemoveCol);
        if (mGameState->mBlocksRemaining > 0) {
          mGameState->mBlocksRemaining--;
        }

        mRemoveCol++;
        break;
      }
    }
    mRemoveCol++;
  }
  return ETrue;
}
