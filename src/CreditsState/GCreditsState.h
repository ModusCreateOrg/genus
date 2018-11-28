#ifndef GENUS_GCREDITSSTATE_H
#define GENUS_GCREDITSSTATE_H

#include <BGameEngine.h>

class GCreditsState : public BGameEngine {
public:
  GCreditsState();

  virtual ~GCreditsState();

public:
  void Render();
public:
  void StartText();

protected:
  BBitmap *mBackground;
};



#endif //GENUS_GCREDITSSTATE_H
