#include "GColorSwapPowerup.h"
#include "GGameState.h"
#include "Game.h"

ANIMSCRIPT ColorSwapAninmation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP1(IMG_POWERUP_COLORSWAP),
  ASTEP1(IMG_POWERUP_COLORSWAP + 1),
  ASTEP1(IMG_POWERUP_COLORSWAP + 2),
  ASTEP1(IMG_POWERUP_COLORSWAP + 3),
  ALOOP
};

class Point : public BNode {
public:
  Point(TInt aRow, TInt aCol) {
    mRow = aRow;
    mCol = aCol;
  }
public:
  TInt mRow, mCol;
};

class PointStack : public BList {
public:
  void Push(Point *p) {
    BList::AddHead((BNode &)*p);
  }

  Point *Pop() { return (Point *) BList::RemHead(); }
  TBool Empty() { return BList::End(BList::First()); }
};

GColorSwapPowerup::GColorSwapPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : BPowerup(aSprite, aGameState) {
  mSprite->mBlockSize = BLOCKSIZE_1x1;
  mSprite->StartAnimation(ColorSwapAninmation);
  mPointStack = new PointStack();
}

GColorSwapPowerup::~GColorSwapPowerup() {
  delete (PointStack *)mPointStack;
}

TBool GColorSwapPowerup::CanDrop() {
  return ETrue; // bomb can be dropped anywhere
}

TBool GColorSwapPowerup::Drop(GGameProcess *aProcess) {
  // disable rendering
  mSprite->flags &= ~SFLAG_RENDER;

  // notify GameState that blocks are being removed
  mGameState->mBlocksRemoving = ETrue;

  // where on the board the bomb was placed
  TInt row = mSprite->BoardRow();
  TInt col = mSprite->BoardCol();

  mColorSwapTimer = 1; // 1st step immediately
  mDropped        = ETrue;

  mSwapColor = mGameBoard->mBoard[row][col];

  auto *stack = (PointStack *)mPointStack;
  stack->Push(new Point(row, col));
  return ETrue;
}


TBool GColorSwapPowerup::Run() {
  if (!mDropped) {
    return ETrue;
  }
  if (mColorSwapTimer--) {
    return ETrue;
  }
  mColorSwapTimer = 30 / 2;        // 1/8 second

  auto *stack = (PointStack *)mPointStack;
  while (Point *p = stack->Pop()) {
    if (p->mRow >= 0 && p->mRow <= BOARD_ROWS && p->mCol >= 0 && p->mCol < BOARD_COLS) {
      if (mGameBoard->mBoard[p->mRow][p->mCol] == mSwapColor) {
        mGameBoard->mBoard[p->mRow][p->mCol] = TUint8((mSwapColor == IMG_TILE1 ? IMG_TILE2 : IMG_TILE1)+1);
        stack->Push(new Point(p->mRow-1, p->mCol));
        stack->Push(new Point(p->mRow+1, p->mCol));
        stack->Push(new Point(p->mRow, p->mCol-1));
        stack->Push(new Point(p->mRow, p->mCol+1));
        delete p;
        return ETrue;
      }
    }
    delete p;
  }
  return EFalse;
}
