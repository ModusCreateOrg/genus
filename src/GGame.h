#ifndef GENUS_GGAME_H
#define GENUS_GGAME_H

#define FRAME_RATE_INFO 0
#undef FRAME_RATE_INFO

#include "Game.h"

enum {
  GAME_STATE_SPLASH,
  GAME_STATE_MAIN_MENU,
  GAME_STATE_GAME,
  GAME_STATE_GAMEOVER,
  GAME_STATE_HIGH_SCORES,
  GAME_STATE_MAIN_OPTIONS,
  GAME_STATE_MAIN_OPTIONS_RESET,
  GAME_STATE_CREDITS,
  GAME_STATE_RULES,
};

class GGame : public BApplication {
public:
  GGame();
  virtual ~GGame();
public:
  void Run();
public:
  void SetState(TInt aNewState);

protected:
  TInt mState;
  TInt mNextState;
};

extern GGame *gGame;

#endif //GENUS_GGAME_H
