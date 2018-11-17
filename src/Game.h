#ifndef GAME_H
#define GAME_H

// Used by GLevel super classes to enable/disable parallax scrolling
#define STATIC_GAME_BACKGROUNDS (1)
//#undef STATIC_GAME_BACKGROUNDS

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
#include "GameOverState/GGameOverState.h"
#include "HighScoresState/GHighScoresState.h"
#include "MainOptionsState/GMainOptionsState.h"
#include "GCreditsState.h"

// globals
extern BViewPort   *gViewPort;
extern BGameEngine *gGameEngine;
extern TOptions    *gOptions;

#endif
