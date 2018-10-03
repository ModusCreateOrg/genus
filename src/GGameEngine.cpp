#include "Game.h"

GGameEngine::GGameEngine() : BGameEngine(gViewPort) {
  mPlayfield = ENull;
  SetState(GAME_STATE_SPLASH);
}

void GGameEngine::Reset() {
//  gControls.Reset();
//  BGameEngine::Reset();
  mProcessList->Genocide();
  mSpriteList->Reset();
  delete mPlayfield;
  mPlayfield = ENull;
  // stop sounds?
}

TInt GGameEngine::SetState(TInt aNewState) {
  TInt oldState = mState;
  switch (aNewState) {
    case GAME_STATE_SPLASH:
      Reset();
      mPlayfield = new GSplashState(this);
      break;
    case GAME_STATE_MAIN_MENU:
      Reset();
      mPlayfield = new GMainMenuState(this);
      break;
    case GAME_STATE_GAME:
      Reset();
      mPlayfield = new GGameState(this);
      break;
    case GAME_STATE_GAMEOVER:
      Reset();
      mPlayfield = new GGameOverState(this);
      break;
    case GAME_STATE_ENTER_HIGHSCORE:
      Reset();
      mPlayfield = new GEnterHighScoreState(this);
      break;
    case GAME_STATE_HIGH_SCORES:
      Reset();
      mPlayfield = new GHighScoresState(this);
      break;
    case GAME_STATE_MAIN_OPTIONS:
      Reset();
      mPlayfield = new GMainOptionsState(this);
      break;
    case GAME_STATE_CREDITS:
      Reset();
      mPlayfield = new GCreditsState(this);
      break;
    default:
      return oldState;
  }
  // reset dKeys so next state doesn't react to any keys already pressed
  gControls.dKeys = 0;
  return oldState;
}
