#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

#include "Game.h"

// number of rows and columns in the game board
static const TInt GAMEBOARD_ROWS = 11;
static const TInt GAMEBOARD_COLS = 8;

static const TInt BOARDX = ((320 - (GAMEBOARD_COLS*16)) / 2);
static const TInt BOARDY = (240 - 16 - (GAMEBOARD_ROWS*16));
static const TFloat PLAYERX = BOARDX + 48;
static const TFloat PLAYERY = BOARDY - 32;
static const TFloat PLAYERX_MIN = PLAYERX;
static const TFloat PLAYERX_MAX = PLAYERX + (GAMEBOARD_COLS-2)*16;

class GPlayerSprite;

class GGameState : public BPlayfield {
public:
  GGameState(GGameEngine *aGameEngine);

  virtual ~GGameState();

public:
  void Render();

  void Animate();

protected:
  BBitmap *mBackground1, *mBackground2;
  BBitmap *mCurrentBackground;
  TInt    mAnimationTimer;

public:
  TInt mLevel;
  TBCD mScore;
  TInt mBeat;
  TInt mTimer;
  TInt8 mGameBoard[GAMEBOARD_ROWS][GAMEBOARD_COLS];
public:
  void Clear();
  void LoadLevel();

};

#endif //GENUS_GGAMESTATE_H
