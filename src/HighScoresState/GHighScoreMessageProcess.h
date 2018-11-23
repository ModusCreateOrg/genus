#ifndef GENUS_GHIGHSCOREMESSAGEPROCESS_H
#define GENUS_GHIGHSCOREMESSAGEPROCESS_H

#include "Game.h"

class GHighScoreMessageProcess : public BProcess {
public:
  GHighScoreMessageProcess();
  ~GHighScoreMessageProcess();

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

#endif //GENUS_GHIGHSCOREMESSAGEPROCESS_H
