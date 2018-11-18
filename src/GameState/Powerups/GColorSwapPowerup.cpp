#include "Game.h"
#include "GColorSwapPowerup.h"

static ANIMSCRIPT ColorSwapAninmation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP(30, IMG_POWERUP_COLORSWAP),
  ASTEP1(IMG_POWERUP_COLORSWAP + 1),
  ASTEP1(IMG_POWERUP_COLORSWAP + 2),
  ASTEP1(IMG_POWERUP_COLORSWAP + 3),
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
  mColorSwapTimer = 30 / 8;        // 1/8 second

  auto         *stack = (PointStack *) mPointStack;
  while (Point *p     = stack->Pop()) {
    if (p->mRow >= 0 && p->mRow <= BOARD_ROWS && p->mCol >= 0 && p->mCol < BOARD_COLS) {
      if (mGameBoard->mBoard[p->mRow][p->mCol] == mSwapColor) {
        gSoundPlayer.PlaySound(/*SFX_GOOD_DROP_BLOCK_WAV*/0, 0, EFalse);
        mGameBoard->mBoard[p->mRow][p->mCol] = TUint8(mSwapColor == IMG_TILE1 ? IMG_TILE2 : IMG_TILE1);
        printf("%d,%d = %d\n", p->mRow, p->mCol, mGameBoard->mBoard[p->mRow][p->mCol]);
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
  mGameState->Next(EFalse);
  return EFalse;
}


TBool GColorSwapPowerup::StateMove() {
  mRepeatTimer--;

  if (TimedControl(JOYLEFT)) {
    MoveLeft();
  } else if (TimedControl(JOYRIGHT)) {
    MoveRight();
  } else if (TimedControl(JOYUP)) {
    MoveUp();
  } else if (TimedControl(JOYDOWN)) {
    MoveDown();
  }

  if (gControls.WasPressed(BUTTON_SELECT)) {
    if (mGameBoard->mBoard[mPlayerSprite->BoardRow()][mPlayerSprite->BoardCol()] != 255) {
      Drop();
      mState = STATE_REMOVE;
    }
    else {
      // make bad drop sound
      gSoundPlayer.PlaySound(/*SFX_BAD_DROP_BLOCK_WAV*/1, 0, EFalse);
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
