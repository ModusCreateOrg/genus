/**
 * This code controls the state where game is over, user has hit any button, and now we need to determine if
 * his score is good enough to make the high score table.
 */

#include "Game.h"
#include "GGameOverProcess.h"
#include "GGameOverPlayfield.h"

GGameOverState::GGameOverState() : BGameEngine(gViewPort) {
  mPlayfield = new GGameOverPlayfield();
  AddProcess(new GGameOverProcess());
}

GGameOverState::~GGameOverState() {
//  delete mPlayfield;
}

