#include "Game.h"

#ifdef __XTENSA__
#include "freeRTOS/task.h"
#else

#include "SDL2/SDL.h"
#include <stdio.h>

#endif

const int FRAMERATE = 30;


BViewPort   *gViewPort;
GGameEngine *gGameEngine;

// For demo purposes
TUint8 currentSfx = 0,
        maxSfx = 8;

bool muted = false;

TInt32 frame = 0;
/** @file
 * \brief Main entry point for game engine.
 *
 * Initializes the engine and runs the main event loop.
 */
extern "C" void app_main() {
  SeedRandom(time(ENull));
  gDisplay.Init();
  soundPlayer.Init(4, 9);

  // TODO: this belongs in GGameEngine
  gResourceManager.LoadBitmap(CHARSET_BMP, FONT_SLOT, IMAGE_8x8);

  gViewPort = new BViewPort();
  gViewPort->Offset(50, 50);
  gViewPort->SetRect(TRect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1));

  gGameEngine = new GGameEngine();

  TBool done = EFalse;

  while (!done) {

    Random(); // randomize
    gGameEngine->GameLoop();
    gDisplay.Update();
    if (gControls.WasPressed(BUTTONQ)) {
      done = true;
    }

    if (gControls.WasPressed(BUTTONA)) {
      printf("BUTTON A\n");
      soundPlayer.PlayMusic(STAGE_5_XM);
    }

    if (gControls.WasPressed(BUTTON3)) {
      printf("MENU BUTTON\n");
      soundPlayer.MuteMusic(muted = !muted);
      printf("Muting %i\n", muted);
    }


    frame++;
    if (frame % 30 == 0) {
      if (currentSfx > maxSfx) {
        currentSfx = 0;
      }
      soundPlayer.PlaySound(currentSfx, 0);
      currentSfx++;
    }

    if (frame == 200) {
      soundPlayer.PlayMusic(STAGE_2_XM);
    }


    if (gControls.WasPressed(BUTTONB)) {
      printf("BUTTON B\n"); fflush(stdout);
      if (currentSfx > maxSfx) {
        currentSfx = 0;
      }
      soundPlayer.PlaySound(currentSfx, 0);
      currentSfx++;
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
