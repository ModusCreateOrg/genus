#include "GGameOverHighScoreAnimationProcess.h"
#include "Game.h"

static ANIMSCRIPT HighScoresAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP(15, IMG_HIGH_SCORES1),
  ASTEP(15, IMG_HIGH_SCORES1 + 1),
  ALOOP
};

GGameOverHighScoreAnimationProcess::GGameOverHighScoreAnimationProcess(GGameOverState *aGameOverState) : BProcess() {
  mGameOverState = aGameOverState;
  gResourceManager.LoadBitmap(HIGH_SCORES_ANIMATION1_BMP, COMMON_SLOT, IMAGE_64x64);
  mSprite = new BAnimSprite(1, COMMON_SLOT);
  mSprite->x = 240;
  mSprite->y = 124;
  mSprite->StartAnimation(HighScoresAnimation);
  mGameOverState->AddSprite(mSprite);
}

GGameOverHighScoreAnimationProcess::~GGameOverHighScoreAnimationProcess() {
}

TBool GGameOverHighScoreAnimationProcess::RunBefore() {
  return ETrue;
}

TBool GGameOverHighScoreAnimationProcess::RunAfter() {
  return ETrue;
}

