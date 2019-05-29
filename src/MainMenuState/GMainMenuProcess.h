#ifndef GENUS_GMAINMENUPROCESS_H
#define GENUS_GMAINMENUPROCESS_H

#include "Game.h"
#include "GMainMenuContainer.h"
#include "GContinueGameContainer.h"

static const TInt TIMEOUT = 30 * 5;

class GMainMenuProcess : public BProcess {
public:
  GMainMenuProcess();
  ~GMainMenuProcess();

public:
  void ResetTimer();
  void SwitchContainer(TInt8 aContainerType);
  TBool RunBefore();
  TBool RunAfter();


private:
  TInt8 mNewContainerToRender;
  TBool mSwitchContainer;
  TBool mShowHighScores;
  TInt mTimer;
  GDialogWidget *mContainer;
};

#endif //GENUS_GMAINMENUPROCESS_H
