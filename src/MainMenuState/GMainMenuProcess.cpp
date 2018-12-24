#include "GMainMenuProcess.h"

GMainMenuProcess::GMainMenuProcess() : BProcess() {
  mTimer = TIMEOUT;
  mShowHighScores = ETrue;
  mSwitchContainer = EFalse;
  mContainer = new GMainMenuContainer(0, 0, this);
}

GMainMenuProcess::~GMainMenuProcess() {
  delete mContainer;
}

void GMainMenuProcess::ResetTimer() {
  mTimer = TIMEOUT;
}

void GMainMenuProcess::SwitchContainer() {
  mSwitchContainer = ETrue;
  mShowHighScores = EFalse;
}

TBool GMainMenuProcess::RunBefore() {
  if (mSwitchContainer) {
    delete mContainer;
    mContainer = new GContinueContainer(0, 20, this);
    mSwitchContainer = EFalse;
  }

  mContainer->Render(120, 120);
  mContainer->Run();
  return ETrue;
}

TBool GMainMenuProcess::RunAfter() {
  if (gControls.WasPressed(BUTTON_START)) {
    gGame->SetState(GAME_STATE_GAME);
    return EFalse;
  } else if (gControls.WasPressed(BUTTON_MENU)) {
    gGame->SetState(GAME_STATE_MAIN_OPTIONS);
    return EFalse;
  }
  if (mShowHighScores && --mTimer < 0) {
    gGame->SetState(GAME_STATE_HIGH_SCORES);
    return EFalse;
  }
  return ETrue;
}
