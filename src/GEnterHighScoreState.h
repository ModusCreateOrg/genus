#ifndef GENUS_GENTERHIGHSCORESTATE_H
#define GENUS_GENTERHIGHSCORESTATE_H

#include <BPlayfield.h>
#include "GGameEngine.h"

class GEnterHighScoreState : public BPlayfield {
public:
  GEnterHighScoreState(GGameEngine *aGameEngine);

  virtual ~GEnterHighScoreState();

public:
  void Render();

protected:
  BBitmap *mBackground;
};


#endif //GENUS_GENTERHIGHSCORESTATE_H
