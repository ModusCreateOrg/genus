#include "Game.h"

BViewPort   *gViewPort;
GGameEngine *gGameEngine;

/** @file
 * \brief Main entry point for game engine.
 *
 * Initializes the engine and runs the main event loop.
 */
extern "C" void app_main() {
  SeedRandom(300);
  gDisplay.Init();

  // TODO: this belongs in GGameEngine
  gResourceManager.LoadBitmap(CHARSET_BMP, FONT_SLOT, IMAGE_8x8);

  gViewPort = new BViewPort();
  gViewPort->Offset(0, 0);
  gViewPort->SetRect(TRect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));

  gGameEngine = new GGameEngine();

  TBool done = EFalse;

  while (!done) {
    Random(); // ranndomize
    gGameEngine->GameLoop();
    gDisplay.Update();
    if (gControls.WasPressed(BUTTONQ)) {
      done = true;
    }
  }

  printf("Exiting\n");
}

#ifndef __XTENSA__

int main() {
  app_main();
  return 0;
}

#endif
