#ifndef GENUS_GGAMEOVERSTATE_H
#define GENUS_GGAMEOVERSTATE_H


#include <BGameEngine.h>

class GGameOverState : public BGameEngine {
public:
  GGameOverState();

  virtual ~GGameOverState();

public:
  void Render();

protected:
  BBitmap *mBackground;
};


#endif //GENUS_GGAMEOVERSTATE_H
