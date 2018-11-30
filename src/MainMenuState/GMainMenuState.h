#ifndef GENUS_GMAINMENUSTATE_H
#define GENUS_GMAINMENUSTATE_H

#include <BPlayfield.h>

class GMainMenuState : public BGameEngine {
public:
  GMainMenuState();

  virtual ~GMainMenuState();

public:
  BProcess *mMainMenuProcess;

private:
  BFont *mFont16;
};

#endif //GENUS_GMAINMENUSTATE_H
