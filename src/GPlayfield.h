//
// Created by Michael Schwartz on 9/5/18.
//

#ifndef GAME_ENGINE_GPLAYFIELD_H
#define GAME_ENGINE_GPLAYFIELD_H

#include <BPlayfield.h>
#include <BBitmap.h>

class GGameEngine;

class GPlayfield : public BPlayfield {
public:
  GPlayfield(GGameEngine *aGameEngine);
public:
  void Render();
protected:
  GGameEngine *mGameEngine;
  BBitmap *mBitmap;
};


#endif //GAME_ENGINE_GPLAYFIELD_H
