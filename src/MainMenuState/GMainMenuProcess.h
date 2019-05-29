#ifndef GENUS_GMAINMENUPROCESS_H
#define GENUS_GMAINMENUPROCESS_H

#include "Game.h"
#include "GMainMenuContainer.h"
#include "GContinueContainer.h"

static const TInt TIMEOUT = 30 * 5;

class GMainMenuProcess : public BProcess {
public:
  GMainMenuProcess();
  ~GMainMenuProcess();

public:
  void ResetTimer();
  void SwitchContainer();
  TBool RunBefore();
  TBool RunAfter();

private:
  TBool mSwitchContainer;
  TBool mShowHighScores;
  TInt mTimer;
  GDialogWidget *mContainer;
};

#endif //GENUS_GMAINMENUPROCESS_H
