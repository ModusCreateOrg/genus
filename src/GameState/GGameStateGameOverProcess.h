#ifndef GENUS_GGAMEOVERPROCESS_H
#define GENUS_GGAMEOVERPROCESS_H

#include "Game.h"

class GGameStateGameOverProcess : public BProcess {
public:
  GGameStateGameOverProcess(GGameState *aGameState);
  ~GGameStateGameOverProcess();
public:
  TBool RunBefore();
  TBool RunAfter();
protected:
  TInt mTextColor;
  TInt mFrameCounter;
  BAnimSprite *mSprite;
  GGameState *mGameState;
};

#endif //GENUS_GGAMEOVERPROCESS_H
