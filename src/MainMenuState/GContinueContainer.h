#ifndef GENUS_GCONTINUECONTAINER_H
#define GENUS_GCONTINUECONTAINER_H

#include "Game.h"

class GMainMenuProcess;

class GContinueContainer : public GDialogWidget {
public:
  GContinueContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess);
  ~GContinueContainer();
  TBool OnNavigate(TUint16 bits);

public:
  GMainMenuProcess *mProcess;
};

#endif //GENUS_GCONTINUECONTAINER_H
