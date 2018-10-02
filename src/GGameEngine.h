//
// Created by Michael Schwartz on 9/5/18.
//

#ifndef GAME_ENGINE_GGAMEENGINE_H
#define GAME_ENGINE_GGAMEENGINE_H

#include "BGameEngine.h"
#include <Display.h>
#include "GSoundPlayer.h"

class GPlayfield;

class GGameEngine : public BGameEngine {
  friend GPlayfield;
public:
  GGameEngine(BViewPort *aViewPort);
};


#endif //GAME_ENGINE_GGAMEENGINE_H
