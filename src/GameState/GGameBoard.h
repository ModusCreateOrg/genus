#ifndef GENUS_GGAMEBOARD_H
#define GENUS_GGAMEBOARD_H

#include <CreativeEngine.h>

// number of rows and columns in the visible game board
static const TInt VISIBLE_BOARD_ROWS = 12;
static const TInt VISIBLE_BOARD_COLS = 12;
// number of rows and columns in the game board (visible and hidden)
static const TInt BOARD_ROWS         = (VISIBLE_BOARD_ROWS);
static const TInt BOARD_COLS         = (VISIBLE_BOARD_COLS);
//static const TInt BOARD_ROWS         = (VISIBLE_BOARD_ROWS + 8);
//static const TInt BOARD_COLS         = (VISIBLE_BOARD_COLS + 8);
static const TInt BOARD_X_MAX        = (BOARD_COLS - VISIBLE_BOARD_COLS);
static const TInt BOARD_Y_MAX        = (BOARD_ROWS - VISIBLE_BOARD_ROWS);

// screen coordinates
//static const TInt BOARD_X = ((320 - (VISIBLE_BOARD_COLS * 16)) / 2);
//static const TInt BOARD_Y = (240 - 16 - (VISIBLE_BOARD_ROWS * 16));
static const TInt BOARD_X = 8;
static const TInt BOARD_Y = (240 - 12 - (VISIBLE_BOARD_ROWS * 16));
//static const TInt BOARD_Y = (240 - 16 - (VISIBLE_BOARD_ROWS * 16));

class GGameBoard : public BBase {
public:
  GGameBoard();

public:
  void Clear();
  void Render();

protected:
  // mark a block as matched (e.g. turn from blue/pink to blue/pink with black center
  // returns EFalse if the block was already black center
  TBool Mark(TInt aRow, TInt aCol);

  TUint8 GetBlock(TInt aRow, TInt aCol) {
    TUint8 b = mBoard[aRow][aCol];
    if (b != 255) {
      b &= ~8;
    }
    return b;
  }

  TBool GetQuad(TInt aRow, TInt aCol, TUint8 *aQuad) {
    aQuad[0] = GetBlock(aRow, aCol);
    aQuad[1] = GetBlock(aRow, aCol + 1);
    aQuad[2] = GetBlock(aRow + 1, aCol);
    aQuad[3] = GetBlock(aRow + 1, aCol + 1);
    if (aQuad[0] == 255 || aQuad[1] == 255 || aQuad[2] == 255 || aQuad[3] == 255) {
      return EFalse;
    }
    return aQuad[0] == aQuad[1] && aQuad[1] == aQuad[2] && aQuad[2] == aQuad[3];
  }

public:
  TBool Combine();

  TUint32 CountScore();

  TBool IsGameOver();

public:
  TInt    mBoardX, mBoardY;  // scroll position of board

  TUint8  mBoard[BOARD_ROWS][BOARD_COLS];
};


#endif //GENUS_GGAMEBOARD_H
