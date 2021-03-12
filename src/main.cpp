#include "Game.h"

BViewPort   *gViewPort;
BGameEngine *gGameEngine;

GGame    *gGame;
TOptions *gOptions;

#ifdef __MODUS_TARGET_NETWORK_DISPLAY__
#include "NetworkDisplay/NetworkDisplay.h"
#endif

/** @file
 * \brief Main entry point for game engine.
 *
 * Initializes the engine and runs the main event loop.
 */

// app_main
extern "C" void app_main(char *fileName) {

    gGame = new GGame();
#ifdef __MODUS_TARGET_NETWORK_DISPLAY__
    NetworkDisplay *display = (NetworkDisplay*)&gDisplay;
//    const char *fileName = "/home/jgarcia/modite-rgb.ini";
    display->ConfigureFromIniFile(fileName);
#endif
    gGame->Run();
    delete gGame;
}


int main(int argc, char *argv[]) {
#ifdef __MODUS_TARGET_NETWORK_DISPLAY__
  if (argc < 2) {
    printf("Usage: %s <path.to.ini.file>\n", argv[0]);
    return 1;
  }
#endif

    app_main(argv[1]);
    return 0;
}


