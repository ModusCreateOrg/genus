#ifndef GENUS_GGAMEBOARD_H
#define GENUS_GGAMEBOARD_H

#include <CreativeEngine.h>

//
// Design / layout constants
//

// number of rows and columns in the game board (visible and hidden)
static const TInt BOARD_ROWS  = 12;
static const TInt BOARD_COLS  = 12;

//
//
//
class GGameBoard : public BBase {
public:
  GGameBoard();

public:
  void Clear();

  void Render(TInt aX, TInt aY);

protected:
  // mark a block as matched (e.g. turn from blue/pink to blue/pink with black center
  // returns EFalse if the block was already black center
  TBool Mark(TInt aRow, TInt aCol);

  TUint8 GetBlock(TInt aRow, TInt aCol) {
    if (aRow < 0 || aRow > BOARD_ROWS - 1) {
      return 255;
    }
    if (aCol < 0 || aCol > BOARD_COLS - 1) {
      return 255;
    }
    TUint8 b = mBoard[aRow][aCol];
    if (/* b >= 0 &&*/ b <= 5) {
      return 0;
    } else if (b >= 16 && b <= 21) {
      return 16;
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
  void ExplodeBlock(TInt aRow, TInt aCol);
  /**
   * Return ETrue if tile at row, col is empty.
   */
  TBool IsEmpty(TInt aRow, TInt aCol);

public:

  /**
   * Examine board and turn tiles that make a solid 2x2 into removable state
   *
   * @return ETrue if a new 2x2 was found/made
   */
  TBool Combine();

  TBool IsGameOver();

  void Dump();

public:
  TUint8 mBoard[BOARD_ROWS][BOARD_COLS];
};


#endif //GENUS_GGAMEBOARD_H
