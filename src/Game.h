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
#include "TOptions.h"

// GGameEngine states
#include "SplashState/GSplashState.h"
#include "MainMenuState/GMainMenuState.h"
#include "GameState/GGameState.h"
#include "GGameOverState.h"
#include "GEnterHighScoreState.h"
#include "HighScoresState/GHighScoresState.h"
#include "MainOptionsState/GMainOptionsState.h"
#include "GCreditsState.h"

// globals
extern BViewPort   *gViewPort;
extern BGameEngine *gGameEngine;
extern TOptions    *gOptions;

#endif
