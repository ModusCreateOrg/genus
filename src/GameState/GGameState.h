#ifndef GENUS_GGAMESTATE_H
#define GENUS_GGAMESTATE_H

#include "Game.h"
#include "GGameBoard.h"
#include "GGameProcess.h"

static const TFloat PLAYER_X = BOARD_X + 48;
static const TFloat PLAYER_Y = BOARD_Y; //  - 32;
static const TFloat PLAYER_X_MIN = BOARD_X;
static const TFloat PLAYER_X_MAX = BOARD_X + (VISIBLE_BOARD_COLS - 2) * 16;
static const TFloat PLAYER_Y_MIN = BOARD_Y;
static const TFloat PLAYER_Y_MAX = BOARD_Y + (VISIBLE_BOARD_ROWS - 2) * 16;

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
protected:
    BBitmap *mBackground;
protected:
    GGameProcess *mGameProcess;

public:
    TBool mGameOver;
    TInt mLevel;
    TBCD mScore;
    GGameBoard mGameBoard;
public:
    TInt mBonusTime;        // how much time to set bonus timer to (faster = harder)
    TInt mBonusTimer;
    // override BGameEngine PreRender() so we can manage timers
    void PreRender();
    // override PostRender() to draw the scores, etc.
    void PostRender();
public:
    void Clear();

    void LoadLevel();

};

#endif //GENUS_GGAMESTATE_H
