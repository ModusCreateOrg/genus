#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <CreativeEngine.h>
#include "GSoundPlayer.h"
#include "Resources.h"

// Game specific includes
#include "GResources.h"
#include "GGame.h"

// GGameEngine states
#include "GSplashState.h"
#include "GMainMenuState.h"
#include "GameState/GGameState.h"
#include "GGameOverState.h"
#include "GEnterHighScoreState.h"
#include "GHighScoresState.h"
#include "GMainOptionsState.h"
#include "GCreditsState.h"

extern BViewPort   *gViewPort;
extern BGameEngine *gGameEngine;

#endif