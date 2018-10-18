#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

#include "Game.h"
#include "GGameProcess.h"

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

static const TFloat PLAYER_X     = BOARD_X + 48;
static const TFloat PLAYER_Y     = BOARD_Y; //  - 32;
static const TFloat PLAYER_X_MIN = BOARD_X;
static const TFloat PLAYER_X_MAX = BOARD_X + (VISIBLE_BOARD_COLS - 2) * 16;
static const TFloat PLAYER_Y_MIN = BOARD_Y;
static const TFloat PLAYER_Y_MAX = BOARD_Y + (VISIBLE_BOARD_ROWS - 2) * 16;

class GGameState : public BPlayfield {
public:
  GGameState(GGameEngine *aGameEngine);

  virtual ~GGameState();

public:
  void Render() override;

  void Animate() override;

protected:
  BBitmap *mBackground;
  TUint8  mTextColor;
protected:
  GGameProcess *mGameProcess;

public:
  TBool   mGameOver;
  TInt    mLevel;
  TBCD    mScore, mLastScore;
  TUint32 mPoints;
  TInt    mBoardX, mBoardY;  // scroll position of board
  TUint8  mGameBoard[BOARD_ROWS][BOARD_COLS];
public:
  void Clear();

  void LoadLevel();

protected:
  TUint8 GetBlock(TInt aRow, TInt aCol) {
    TUint8 b = mGameBoard[aRow][aCol];
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
  void Combine();

  void CountScore();

  TBool IsGameOver();

};

#endif //GENUS_GGAMESTATE_H
