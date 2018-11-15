#include "GGameOverProcess.h"
#include "Game.h"

GGameOverProcess::GGameOverProcess() {
  mFrameCounter = 0;
}

GGameOverProcess::~GGameOverProcess() {}

TBool GGameOverProcess::RunBefore() {
  if (gControls.WasPressed(BUTTON_ANY)) {
    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }
  return ETrue;
}

TBool GGameOverProcess::RunAfter() {
  mFrameCounter++;
  if (mFrameCounter & 4) {
    gDisplay.SetColor(253, 255, 255, 255);
    BBitmap *bm = gDisplay.renderBitmap;
    bm->DrawBitmapTransparent(ENull, gResourceManager.GetBitmap(COMMON_SLOT), TRect(0, 0, 127, 15),
                              (DISPLAY_WIDTH - 128) / 2, (DISPLAY_HEIGHT - 16) / 2);
  }
  return ETrue;
}
