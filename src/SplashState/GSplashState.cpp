#include "Game.h"
#include "GSplashPlayfield.h"
#include "GDropProcess.h"
#include "GSplashProcess.h"

GSplashState::GSplashState() : BGameEngine(gViewPort) {
  mPlayfield = new GSplashPlayfield();
  AddProcess(new GSplashProcess());
  AddProcess(new GDropProcess(this, 0));
  AddProcess(new GDropProcess(this, 1));
  AddProcess(new GDropProcess(this, 2));
  AddProcess(new GDropProcess(this, 3));
  AddProcess(new GDropProcess(this, 4));
  AddProcess(new GDropProcess(this, 5));
}

GSplashState::~GSplashState() {
//  delete mPlayfield;
}

