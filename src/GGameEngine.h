//
// Created by Michael Schwartz on 9/5/18.
//

#ifndef GAME_ENGINE_GGAMEENGINE_H
#define GAME_ENGINE_GGAMEENGINE_H

#include "BGameEngine.h"
#include "../resources/music/Music.h"
#include <Display.h>

class GPlayfield;

class GGameEngine : public BGameEngine {
  friend GPlayfield;
public:
  GGameEngine(BViewPort *aViewPort);
};


#endif //GAME_ENGINE_GGAMEENGINE_H
