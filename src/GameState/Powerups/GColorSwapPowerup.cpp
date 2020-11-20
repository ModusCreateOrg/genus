#include "Game.h"
#include "GColorSwapPowerup.h"

static const TUint16 SWAP_SPEED = FRAMES_PER_SECOND / 8;


static ANIMSCRIPT ColorSwapAninmation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP(SWAP_SPEED, IMG_POWERUP_COLORSWAP),
  ASTEP(SWAP_SPEED, IMG_POWERUP_COLORSWAP + 1),
  ASTEP(SWAP_SPEED, IMG_POWERUP_COLORSWAP + 2),
  ASTEP(SWAP_SPEED, IMG_POWERUP_COLORSWAP + 3),
  ALOOP
};

/************************************************************************
 ************************************************************************
 ***********************************************************************/

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
    BList::AddHead((BNode &) *p);
  }

  Point *Pop() { return (Point *) BList::RemHead(); }

  TBool Empty() { return BList::End(BList::First()); }
};

/************************************************************************
 ************************************************************************
 ***********************************************************************/

GColorSwapPowerup::GColorSwapPowerup(GPlayerSprite *aSprite, GGameState *aGameState) : BPowerup(aSprite, aGameState) {
  mPlayerSprite->mBlockSize = BLOCKSIZE_1x1;
  mPlayerSprite->StartAnimation(ColorSwapAninmation);
  mPointStack = new PointStack();
  mState      = STATE_MOVE;
}

GColorSwapPowerup::~GColorSwapPowerup() {
  delete (PointStack *) mPointStack;
}

/************************************************************************
 ************************************************************************
 ***********************************************************************/

TBool GColorSwapPowerup::Drop() {
  // disable rendering
  mPlayerSprite->flags &= ~SFLAG_RENDER;

  // where on the board the bomb was placed
  TInt row = mPlayerSprite->BoardRow();
  TInt col = mPlayerSprite->BoardCol();

  mColorSwapTimer = 1; // 1st step immediately

  mSwapColor = mGameBoard->mBoard[row][col];

  auto *stack = (PointStack *) mPointStack;
  stack->Push(new Point(row, col));
  return ETrue;
}


/************************************************************************
 ************************************************************************
 ***********************************************************************/

TBool GColorSwapPowerup::StateRemove() {
  if (mColorSwapTimer--) {
    return ETrue;
  }

  mColorSwapTimer = 30 / 6;        // 1/8 second

  auto         *stack = (PointStack *) mPointStack;
  while (Point *p     = stack->Pop()) {
    if (p->mRow >= 0 && p->mRow < BOARD_ROWS && p->mCol >= 0 && p->mCol < BOARD_COLS) {
      if (mGameBoard->mBoard[p->mRow][p->mCol] == mSwapColor) {
        gSoundPlayer.SfxGoodDrop();

        mGameBoard->mBoard[p->mRow][p->mCol] = TUint8(mSwapColor == IMG_TILE1 ? IMG_TILE2 : IMG_TILE1);

        stack->Push(new Point(p->mRow - 1, p->mCol));
        stack->Push(new Point(p->mRow + 1, p->mCol));
        stack->Push(new Point(p->mRow, p->mCol - 1));
        stack->Push(new Point(p->mRow, p->mCol + 1));
        delete p;
        return ETrue;
      }
    }
    delete p;
  }
  gControls.dKeys = 0;  // in case user pressed a key during removing blocks
  mGameState->Next(EFalse);
  return EFalse;
}


TBool GColorSwapPowerup::StateMove() {
  TUint8 currentColor = mGameBoard->mBoard[mPlayerSprite->BoardRow()][mPlayerSprite->BoardCol()];

  if (gControls.WasPressed(BUTTONB)) {
    // Placeable only on non-darkened blocks and during states other than removal of blocks
    if (mGameState->MainState() != STATE_REMOVE && (currentColor == 0 || currentColor == 16)) {
      Drop();
      mState = STATE_REMOVE;
      mGameState->MainState(STATE_WAIT);
    }
    else {
      // make bad drop sound
      gSoundPlayer.SfxBadDrop();
    }
  }

  return ETrue;
}

TBool GColorSwapPowerup::RunAfter() {
  switch (mState) {
    case STATE_MOVE:
      return StateMove();
    case STATE_REMOVE:
      return StateRemove();
    case STATE_TIMER:
      return StateMove();
    case STATE_WAIT:
      return ETrue;
  }
  return ETrue;
}
