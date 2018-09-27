#ifndef GAME_ENGINE_GPLAYFIELD_H
#define GAME_ENGINE_GPLAYFIELD_H

#include <BPlayfield.h>
#include <BBitmap.h>
#include <BFont.h>

class GGameEngine;

class GPlayfield : public BPlayfield {
public:
  GPlayfield(GGameEngine *aGameEngine);
public:
  void Render();
protected:
  GGameEngine *mGameEngine;
  BBitmap *mBitmap;
  BFont *mFont;
};


#endif //GAME_ENGINE_GPLAYFIELD_H
