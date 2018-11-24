#ifndef GENUS_GHIGHSCOREANIMATIONPROCESS_H
#define GENUS_GHIGHSCOREANIMATIONPROCESS_H

#include "Game.h"

class GHighScoreAnimationProcess : public BProcess {
public:
  GHighScoreAnimationProcess(GHighScoresState *aHighScoresState);
  ~GHighScoreAnimationProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  BAnimSprite      *mSprite;
  GHighScoresState *mHighScoresState;
};

#endif //GENUS_GHIGHSCOREANIMATIONPROCESS_H
