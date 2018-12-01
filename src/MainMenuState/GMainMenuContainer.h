#ifndef GENUS_GMAINMENUCONTAINER_H
#define GENUS_GMAINMENUCONTAINER_H

#include "Game.h"

class GMainMenuProcess;

class GMainMenuContainer : public BDialogWidget {
public:
  GMainMenuContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess);
  ~GMainMenuContainer();
  void Run();

public:
  GMainMenuProcess *mProcess;
};

#endif //GENUS_GMAINMENUCONTAINER_H
