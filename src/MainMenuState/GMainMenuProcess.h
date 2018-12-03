#ifndef GENUS_GMAINMENUPROCESS_H
#define GENUS_GMAINMENUPROCESS_H

#include "Game.h"
#include "GMainMenuContainer.h"

static const TInt TIMEOUT = 30 * 5;

class GMainMenuProcess : public BProcess {
public:
  GMainMenuProcess();
  ~GMainMenuProcess();

public:
  void ResetTimer();
  TBool RunBefore();
  TBool RunAfter();

private:
  TInt mTimer;
  GMainMenuContainer *mContainer;
};

#endif //GENUS_GMAINMENUPROCESS_H
