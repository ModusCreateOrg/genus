#include "GGame.h"

static TUint32 start;

GGame::GGame() {
  // Load Game Options
  gOptions = new TOptions();

  // TODO: Jay - this needs to be in BApplication constructor (I think)
  gSoundPlayer.Init(3, 6);

  gResourceManager.LoadBitmap(CHARSET_16X16_BMP, FONT_16x16_SLOT, IMAGE_16x16);

  gViewPort = new BViewPort();
  gViewPort->Offset(0, 0);
  gViewPort->SetRect(TRect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));

  mState = mNextState = -1;
  gGameEngine = ENull;
  SetState(GAME_STATE_SPLASH);
  start = Milliseconds();
}

GGame::~GGame() {
  delete gGameEngine;
  delete gViewPort;
}

void GGame::SetState(TInt aNewState) {
  mNextState = aNewState;
}

void GGame::Run() {
  TBool muted = gOptions->muted;

  TBool done = EFalse;
  while (!done) {
    Random(); // randomize

    if (mNextState != mState) {
      switch (mNextState) {
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
          continue;
      }
      // reset dKeys so next state doesn't react to any keys already pressed
      gControls.dKeys = 0;
      mState = mNextState;
    }
    gGameEngine->GameLoop();
    gDisplay.Update();
    TUint32 now = Milliseconds(), elapsed = now - start;
    start = now;
//    printf("elapsed %4d\r", elapsed);
    if (gControls.WasPressed(BUTTONQ)) {
      done = true;
    }
    if (gControls.WasPressed(BUTTON2)) {
      muted = !muted;
      gOptions->muted = muted;
      gOptions->Save();
      gSoundPlayer.MuteMusic(muted);
    }
  }
}
