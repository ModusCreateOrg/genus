#include "GHighScoreAnimationProcess.h"
#include "Game.h"

static ANIMSCRIPT HighScoresAnimation[] = {
  ABITMAP(COMMON_SLOT),
  ALABEL,
  ASTEP(15, IMG_HIGH_SCORES1),
  ASTEP(15, IMG_HIGH_SCORES1 + 1),
  ALOOP
};

GHighScoreAnimationProcess::GHighScoreAnimationProcess(GHighScoresState *aHighScoresState) : BProcess() {
  mHighScoresState = aHighScoresState;
  gResourceManager.LoadBitmap(HIGH_SCORES_ANIMATION1_BMP, COMMON_SLOT, IMAGE_64x64);
  mSprite = new BAnimSprite(1, COMMON_SLOT);
  mSprite->x = 240;
  mSprite->y = 124;
  mSprite->StartAnimation(HighScoresAnimation);
  mHighScoresState->AddSprite(mSprite);
}

GHighScoreAnimationProcess::~GHighScoreAnimationProcess() {
}

TBool GHighScoreAnimationProcess::RunBefore() {
  return ETrue;
}

TBool GHighScoreAnimationProcess::RunAfter() {
  return ETrue;
}

