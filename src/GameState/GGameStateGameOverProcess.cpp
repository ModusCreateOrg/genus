#include "GGameStateGameOverProcess.h"
#include "Game.h"

static ANIMSCRIPT GameOverAnimation[] = {
  ABITMAP(GAME_OVER_SLOT),
  ALABEL,
  ASTEP(30, IMG_GAME_OVER1),
  ASTEP(3, IMG_GAME_OVER1 + 1),
  ASTEP(15, IMG_GAME_OVER1),
  ASTEP(3, IMG_GAME_OVER1 + 1),
  ASTEP(8, IMG_GAME_OVER1 + 3),
  ASTEP(15, IMG_GAME_OVER1),
  ASTEP(3, IMG_GAME_OVER1 + 5),
  ASTEP(15, IMG_GAME_OVER1),
  ASTEP(3, IMG_GAME_OVER1 + 1),
  ASTEP(3, IMG_GAME_OVER1 + 2),
  ASTEP(8, IMG_GAME_OVER1),
  ASTEP(3, IMG_GAME_OVER1 + 1),
  ASTEP(3, IMG_GAME_OVER1 + 4),
  ALOOP
};

GGameStateGameOverProcess::GGameStateGameOverProcess(GGameState *aGameState) {
  mFrameCounter = 0;
  mTextColor = 0;
  mGameState = aGameState;
  gResourceManager.LoadBitmap(GAME_OVER_SPRITES1_BMP, GAME_OVER_SLOT, IMAGE_256x64);
  mSprite = new BAnimSprite(1, GAME_OVER_SLOT);
  mGameState->AddSprite(mSprite);
  mSprite->x = 50;
  mSprite->y = 100;
  mSprite->StartAnimation(GameOverAnimation);
}

GGameStateGameOverProcess::~GGameStateGameOverProcess() {
  gResourceManager.ReleaseBitmapSlot(GAME_OVER_SLOT);
}

TBool GGameStateGameOverProcess::RunBefore() {
  if (gControls.WasPressed(BUTTON_ANY)) {
    gGame->SetState(GAME_STATE_GAMEOVER);
    return EFalse;
  }
  return ETrue;
}

TBool GGameStateGameOverProcess::RunAfter() {
  return ETrue;
}
