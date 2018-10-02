#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "GameEngine.h"
#include "GGameEngine.h"
#include "GResources.h"
#include "GSplashState.h"
#include "GMainMenuState.h"
#include "GGameState.h"
#include "GGameOverState.h"
#include "GEnterHighScoreState.h"
#include "GHighScoresState.h"

extern BViewPort   *gViewPort;
extern GGameEngine *gGameEngine;

#endif