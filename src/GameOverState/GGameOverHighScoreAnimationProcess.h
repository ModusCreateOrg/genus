#ifndef GENUS_GGAMEOVERHIGHSCOREANIMATIONPROCESS_H
#define GENUS_GGAMEOVERHIGHSCOREANIMATIONPROCESS_H

#include "Game.h"

class GGameOverHighScoreAnimationProcess : public BProcess {
public:
  GGameOverHighScoreAnimationProcess(GGameOverState *aGameOverState);
  ~GGameOverHighScoreAnimationProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  BAnimSprite    *mSprite;
  GGameOverState *mGameOverState;
};

#endif //GENUS_GGAMEOVERHIGHSCOREANIMATIONPROCESS_H
