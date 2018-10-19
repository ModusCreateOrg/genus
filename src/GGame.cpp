#include "GGame.h"

GGame::GGame() {
  // TODO: Jay - this needs to be in BApplication constructor (I think)
  gSoundPlayer.Init(3, 6);

  gResourceManager.LoadBitmap(CHARSET_BMP, FONT_SLOT, IMAGE_8x8);

  gViewPort = new BViewPort();
  gViewPort->Offset(0, 0);
  gViewPort->SetRect(TRect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));

  // TODO this should be GSplash, which is a BGameEngine
  gGameEngine = new GSplashState();
}

GGame::~GGame() {
  delete gGameEngine;
  delete gViewPort;
}

TInt GGame::SetState(TInt aNewState) {
  TInt oldState   = mState;
  switch (aNewState) {
    case GAME_STATE_SPLASH:
      delete gGameEngine;
      gGameEngine = new GSplashState();
      break;
    case GAME_STATE_MAIN_MENU:
      delete gGameEngine;
      gGameEngine = new GMainMenuState();
      break;
    case GAME_STATE_GAME:
      delete gGameEngine;
      gGameEngine = new GGameState();
      break;
    case GAME_STATE_GAMEOVER:
      delete gGameEngine;
      gGameEngine = new GGameOverState();
      break;
    case GAME_STATE_ENTER_HIGHSCORE:
      delete gGameEngine;
      gGameEngine = new GEnterHighScoreState();
      break;
    case GAME_STATE_HIGH_SCORES:
      delete gGameEngine;
      gGameEngine = new GHighScoresState();
      break;
    case GAME_STATE_MAIN_OPTIONS:
      delete gGameEngine;
      gGameEngine = new GMainOptionsState();
      break;
    case GAME_STATE_CREDITS:
      delete gGameEngine;
      gGameEngine = new GCreditsState();
      break;
    default:
      return oldState;
  }
  // reset dKeys so next state doesn't react to any keys already pressed
  gControls.dKeys = 0;
  return oldState;
}

void GGame::Run() {
  TBool muted = EFalse;

  TBool done = EFalse;
  while (!done) {
    Random(); // randomize
    gGameEngine->GameLoop();
    gDisplay.Update();
    if (gControls.WasPressed(BUTTONQ)) {
      done = true;
    }
    if (gControls.WasPressed(BUTTON2)) {
      muted = !muted;
      gSoundPlayer.MuteMusic(muted);
    }
  }
}
