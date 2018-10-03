#ifndef GENUS_GHIGHSCORESSTATE_H
#define GENUS_GHIGHSCORESSTATE_H

#include <BPlayfield.h>
#include "GGameEngine.h"

class GHighScoresState : public BPlayfield {
public:
  GHighScoresState(GGameEngine *aGameEngine);

  virtual ~GHighScoresState();

public:
  void Render();

protected:
  BBitmap *mBackground;
};

#endif //GENUS_GHIGHSCORESSTATE_H
