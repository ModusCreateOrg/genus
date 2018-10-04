#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <GameEngine.h>

// Game specific includes
#include "GResources.h"
#include "GGameEngine.h"

// GGameEngine states
#include "GSplashState.h"
#include "GMainMenuState.h"
#include "GGameState.h"
#include "GGameOverState.h"
#include "GEnterHighScoreState.h"
#include "GHighScoresState.h"
#include "GMainOptionsState.h"
#include "GCreditsState.h"

extern BViewPort   *gViewPort;
extern GGameEngine *gGameEngine;

#endif