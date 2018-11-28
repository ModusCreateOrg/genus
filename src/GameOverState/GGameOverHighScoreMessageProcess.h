#ifndef GENUS_GGAMEOVERHIGHSCOREMESSAGEPROCESS_H
#define GENUS_GGAMEOVERHIGHSCOREMESSAGEPROCESS_H

#include "Game.h"

class GGameOverHighScoreMessageProcess : public BProcess {
public:
  GGameOverHighScoreMessageProcess();
  ~GGameOverHighScoreMessageProcess();

public:
  TBool RunBefore();

  TBool RunAfter();

protected:
  void RenderText();
  TBool FadeInState();
  TBool FadeOutState();
  TBool WaitState();
protected:
  enum {
    STATE_FADEIN,
    STATE_FADEOUT,
    STATE_WAIT,
  } mState;
  TInt mTimer;
  TInt mColor;
  BFont *mFont;
  const char *mCurrentText;
};

#endif //GENUS_GGAMEOVERHIGHSCOREMESSAGEPROCESS_H
