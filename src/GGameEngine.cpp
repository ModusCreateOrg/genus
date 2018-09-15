//
// Created by Michael Schwartz on 9/5/18.
//

#include "GGameEngine.h"
#include "GPlayfield.h"

//#define FRAMERATE 30

class BViewPort;

GGameEngine::GGameEngine(BViewPort *aViewPort) : BGameEngine(aViewPort) {
  mPlayfield = new GPlayfield(this);
}