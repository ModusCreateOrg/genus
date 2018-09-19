#include "GGameEngine.h"
#include "GPlayfield.h"

//#define FRAMERATE 30

class BViewPort;

GGameEngine::GGameEngine(BViewPort *aViewPort) : BGameEngine(aViewPort) {
  mPlayfield = new GPlayfield(this);
}
