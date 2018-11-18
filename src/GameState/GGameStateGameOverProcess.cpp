#include "GGameStateGameOverProcess.h"
#include "Game.h"

GGameStateGameOverProcess::GGameStateGameOverProcess() {
  mFrameCounter = 0;
  mTextColor = 0;
  mState = STATE_FADEIN;
}

GGameStateGameOverProcess::~GGameStateGameOverProcess() {}

TBool GGameStateGameOverProcess::RunBefore() {
  if (gControls.WasPressed(BUTTON_ANY)) {
    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }
  return ETrue;
}

void GGameStateGameOverProcess::Render() {
  mFrameCounter++;
  if (mFrameCounter & 4) {
    gDisplay.SetColor(253, 255, 255, 255);
    BBitmap *bm = gDisplay.renderBitmap;
    bm->DrawBitmapTransparent(ENull, gResourceManager.GetBitmap(COMMON_SLOT), TRect(0, 0, 127, 15),
                              (DISPLAY_WIDTH - 128) / 2, (DISPLAY_HEIGHT - 16) / 2);
  }
}

TBool GGameStateGameOverProcess::RunAfter() {
  Render();
  return ETrue;
}
