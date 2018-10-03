#ifndef GAME_ENGINE_GGAMEENGINE_H
#define GAME_ENGINE_GGAMEENGINE_H

#include <BGameEngine.h>
#include <Display.h>

static const TInt GAME_STATE_SPLASH          = 0,
                  GAME_STATE_MAIN_MENU       = 1,
                  GAME_STATE_GAME            = 2,
                  GAME_STATE_GAMEOVER        = 3,
                  GAME_STATE_ENTER_HIGHSCORE = 4,
                  GAME_STATE_HIGH_SCORES     = 5,
                  GAME_STATE_MAIN_OPTIONS    = 6,
                  GAME_STATE_CREDITS         = 7;

class GGameEngine : public BGameEngine {
public:
  GGameEngine();

public:
  void Reset();

  TInt SetState(TInt aNewState);

  TInt GetState() { return mState; }

protected:
  TInt mState;
};

#endif //GAME_ENGINE_GGAMEENGINE_H
