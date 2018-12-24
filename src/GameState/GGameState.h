#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

//#include "Game.h"
#include "Powerups.h"
#include "GGameBoard.h"

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

//
// SCREEN LAYOUT
//

// screen coordinates of the board
static const TInt BOARD_X = 18;
static const TInt BOARD_Y = 34;

// screen coordinates of the bonus timer
static const TInt  TIMER_X = 16;
static const TInt  TIMER_Y = 10;
static const TRect TIMER_BORDER(64, 10, 207, 25);
static const TRect TIMER_INNER(66, 12, 205, 23);

// screen coordinates of the score
static const TInt SCORE_X = 224;
static const TInt SCORE_Y = 10;

// screen coordinates of level display
static const TInt LEVEL_X = 224;
static const TInt LEVEL_Y = 48;

// screen coordinates of moves remaining display
static const TRect MOVES_BORDER(224+4, 73, 303+4, 88);
static const TRect MOVES_INNER(226+4, 75, 301+4, 86);

// screen coordinates of Next
static const TInt NEXT_X       = 224;
static const TInt NEXT_Y       = 144;
static const TInt NEXT_BLOCK_X = 226;
static const TInt NEXT_BLOCK_Y = 168;

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

static const TFloat PLAYER_X     = BOARD_X + 48 + 32;
static const TFloat PLAYER_Y     = BOARD_Y; //  - 32;
static const TFloat PLAYER_X_MIN = BOARD_X;
static const TFloat PLAYER_X_MAX = BOARD_X + (BOARD_COLS - 2) * 16;
static const TFloat PLAYER_Y_MIN = BOARD_Y;
static const TFloat PLAYER_Y_MAX = BOARD_Y + (BOARD_ROWS - 2) * 16;

/****************************************************************************************************************
 ****************************************************************************************************************
 ****************************************************************************************************************/

class GGameState : public BGameEngine {
public:
  GGameState();

  virtual ~GGameState();

public:
  void StartBonusTimer() {
    if (mBonusTimer < 0) {
      mBonusTimer = mBonusTime;
    }
  }

  TPowerUpStates MainState() {
    return mGameProcess->State();
  }

  void MainStateWait() {
    mGameProcess->Wait();
  }

  void SetBlocksPerLevel();

  void SaveState();
  void LoadState();
  void LoadPlayerState();

  // make next sprite current sprite, randomize next sprite
  // maybe randomize powerup if aCanPowerup is true
  void Next(TBool aCanPowerup);

protected:
  BBitmap *mBackground;
protected:
  GNoPowerup *mGameProcess;

public:
  BFont      *mFont8, *mFont16;
  TBool      mGameOver;
  TInt       mLevel;
  TBCD       mScore;
  GPlayerSprite *mSprite, *mNextSprite;
  GGameBoard mGameBoard;

public:
  TInt mBonusTime;        // how much time to set bonus timer to (faster = harder)
  TInt mBonusTimer;

public:
  TInt  mBlocksThisLevel;  // number of moves this level
  TInt  mBlocksRemaining;  // remaining moves this level

private:
  // these used by PostRender()
  void RenderTimer();

  void RenderScore();

  void RenderLevel();

  void RenderMovesLeft();

  void RenderNext();

public:
  // override BGameEngine PreRender() so we can manage timers
  void PreRender();

  // override PostRender() to draw the scores, etc.
  void PostRender();

public:
  void LoadLevel(TBool aForceStageLoad = EFalse);
  void GameOver();

};

#endif //GENUS_GGAMESTATE_H
