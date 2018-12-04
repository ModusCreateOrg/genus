#include "GMainMenuProcess.h"

GMainMenuProcess::GMainMenuProcess() : BProcess() {
  mTimer = TIMEOUT;
  mContainer = new GMainMenuContainer(0, 0, this);
}

GMainMenuProcess::~GMainMenuProcess() {
  delete mContainer;
}

void GMainMenuProcess::ResetTimer() {
  mTimer = TIMEOUT;
}

TBool GMainMenuProcess::RunBefore() {
  mContainer->Render(120, 148);
  mContainer->Run();
  return ETrue;
}

TBool GMainMenuProcess::RunAfter() {
  if (gControls.WasPressed(BUTTON_START)) {
    // @michael Fix this
    gGame->SetState(GAME_STATE_RULES);
//    gGame->SetState(GAME_STATE_GAME);
    return EFalse;
  } else if (gControls.WasPressed(BUTTON_MENU)) {
    gGame->SetState(GAME_STATE_MAIN_OPTIONS);
    return EFalse;
  }
  mTimer--;
  if (mTimer < 0) {
    gGame->SetState(GAME_STATE_HIGH_SCORES);
    return EFalse;
  }
  return ETrue;
}
