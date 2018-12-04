#ifndef GENUS_GRULESSTATE_H
#define GENUS_GRULESSTATE_H

#include <BGameEngine.h>

class GRulesState : public BGameEngine {
public:
  GRulesState();
  virtual ~GRulesState();
public:
  void Render();

protected:
  BBitmap *mBackground;
};


#endif //GENUS_GRULESSTATE_H
