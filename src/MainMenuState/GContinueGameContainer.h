#ifndef GENUS_GCONTINUEGAMECONTAINER_H
#define GENUS_GCONTINUEGAMECONTAINER_H

#include "Game.h"

class GMainMenuProcess;

class GContinueGameContainer : public GDialogWidget {
public:
  GContinueGameContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess);
  ~GContinueGameContainer();
  TBool OnNavigate(TUint16 bits);

public:
  GMainMenuProcess *mProcess;
};

#endif //GENUS_GCONTINUEGAMECONTAINER_H
