#ifndef GENUS_GGAMEOVERPROCESS_H
#define GENUS_GGAMEOVERPROCESS_H

#include "Game.h"

class GGameOverProcess : public BProcess {
public:
  GGameOverProcess();
  ~GGameOverProcess();

public:
  TBool RunBefore();

  TBool RunAfter();

protected:
  TInt CenterText8(const char *s, TInt aY, TInt aColor = COLOR_TEXT, TInt aBackground = -1);
  TInt CenterText16(const char *s, TInt aY, TInt aColor = COLOR_TEXT, TInt aBackground = -1);
  TBool InitialsState();
  TBool HighScoresState();
protected:
  BFont *mFont8, *mFont16;
  enum {
    STATE_INITIALS,
    STATE_HIGHSCORES,
  } mState;
  THighScoreTable mHighScoreTable;
  TInt mScoreIndex; // -1 means not a high score
  char mInitials[SIZE_INITIALS];
  TInt mInitialsPos;
};


#endif //GENUS_GGAMEOVERPROCESS_H
