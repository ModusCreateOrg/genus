#include "GMainMenuProcess.h"

GMainMenuProcess::GMainMenuProcess() : BProcess() {
  mTimer = TIMEOUT;
  mShowHighScores = ETrue;
  mSwitchContainer = EFalse;
  mContainer = new GMainMenuContainer(0, 0, this);
  mNewContainerToRender = -1;
}

GMainMenuProcess::~GMainMenuProcess() {
  delete mContainer;
}

void GMainMenuProcess::ResetTimer() {
  mTimer = TIMEOUT;
}

// 0 : GMainMenuContainer
// 1 : GContinueGameContainer
void GMainMenuProcess::SwitchContainer(TInt8 aContainerType) {
  mSwitchContainer = ETrue;
  mShowHighScores = EFalse;
  mNewContainerToRender = aContainerType;
}

TBool GMainMenuProcess::RunBefore() {
  if (mSwitchContainer) {
    delete mContainer;

    if (mNewContainerToRender == 0) {
      mContainer = new GMainMenuContainer(0, 0, this);
    }
    else if (mNewContainerToRender == 1) {
      mContainer = new GContinueGameContainer(0, 0, this);
    }
    mSwitchContainer = EFalse;
    mNewContainerToRender = -1;
  }

  return ETrue;
}

TBool GMainMenuProcess::RunAfter() {
//  if (gControls.WasPressed(BUTTON_START)) {
//
//    if (gOptions->gameProgress.savedState) {
//      SwitchContainer();
//      return EFalse;
//    }
//    else {
//      gGame->SetState(GAME_STATE_GAME);
//    }
//
//    return EFalse;
//  }


  mContainer->Render(120, 120);
  mContainer->Run();

  if (gControls.WasPressed(BUTTON_MENU)) {
    gGame->SetState(GAME_STATE_MAIN_OPTIONS);
    return EFalse;
  }
  if (mShowHighScores && --mTimer < 0) {
    gGame->SetState(GAME_STATE_HIGH_SCORES);
    return EFalse;
  }
  return ETrue;
}
