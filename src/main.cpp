#include "Game.h"


//#define __XTENSA__
#ifdef __XTENSA__
#include "freeRTOS/task.h"
#else

#include "SDL2/SDL.h"
#include <stdio.h>

#endif

const int FRAMERATE = 30;

GGameEngine *gameEngine;

#define DELTA_V .5

class GDemoProcess : public BProcess {
public:
    GDemoProcess() : BProcess(PTYPE_USER) {
      mPropToggle = EFalse;
      mSprite = new BSprite(0, PLAYER_SLOT, 0);
      mSprite->x = mSprite->y = 0;
      gameEngine->AddSprite(mSprite);
    }

    TBool RunBefore() {
      BBitmap *bm = display.displayBitmap;
      if (mPropToggle) {
        bm->SetColor(200, 151, 151, 151);
        bm->SetColor(201, 238, 238, 238);
        bm->SetColor(202, 255, 0, 0);
        bm->SetColor(203, 255, 255, 0);
      } else {
        bm->SetColor(200, 238, 238, 238);
        bm->SetColor(201, 151, 151, 151);
        bm->SetColor(202, 255, 255, 0);
        bm->SetColor(203, 255, 0, 0);
      }
      mPropToggle = !mPropToggle;
      if (controls.WasPressed(JOYLEFT)) {
        mSprite->vx += -DELTA_V;
      } else if (controls.WasPressed(JOYRIGHT)) {
        mSprite->vx += DELTA_V;
      }
      if (controls.WasPressed(JOYUP)) {
        mSprite->vy += -DELTA_V;
      } else if (controls.WasPressed(JOYDOWN)) {
        mSprite->vy += DELTA_V;
      }
      return ETrue;
    }

    TBool RunAfter() {
      return ETrue;
    }

    TBool mPropToggle;
    BSprite *mSprite;
};


class GDemoProcess2 : public BProcess {
public:
    GDemoProcess2() : BProcess(PTYPE_USER) {
      mSprite = new BSprite(0, PLAYER_SLOT, 3);
      mSprite->x = mSprite->y = 100;
      gameEngine->AddSprite(mSprite);
    }

    TBool RunBefore() {
      if (controls.WasPressed(BUTTON1)) {
        mSprite->flags ^= SFLAG_FLIP;
      }
      if (controls.WasPressed(BUTTON2)) {
        mSprite->flags ^= SFLAG_FLOP;

      }
      return ETrue;
    }

    TBool RunAfter() {
      return ETrue;
    }

    BSprite *mSprite;
};

BViewPort *viewPort;

uint8_t currentSfx = 0,
        maxSfx = 8;

bool muted = false;

TInt32 frame = 0;
extern "C" void app_main() {
//  SeedRandom(time(ENull));
  display.Init();
  soundPlayer.Init(4, 9);

  //Have to seed LibXMP with an empty so we can get the engine running
  soundPlayer.PlayMusic(EMPTYSONG_XM);


  // TODO: this belongs in GGameEngine
  gResourceManager.LoadBitmap(CHARSET_BMP, FONT_SLOT, IMAGE_8x8);
  gResourceManager.LoadBitmap(PLAYERNEW_BMP, PLAYER_SLOT, IMAGE_32x32);
  BBitmap *b = gResourceManager.GetBitmap(PLAYER_SLOT);
  display.SetPalette(b);
  gResourceManager.LoadBitmap(BKG3_BMP, BKG_SLOT, IMAGE_ENTIRE);
  b = gResourceManager.GetBitmap(BKG_SLOT);
//  display.SetPalette(b);



  viewPort = new BViewPort();
  viewPort->Offset(50, 50);
  viewPort->SetRect(b->Dimensions());

  gameEngine = new GGameEngine(viewPort);

  auto *p = new GDemoProcess();
  gameEngine->AddProcess(p);
  auto *p2 = new GDemoProcess2();
  gameEngine->AddProcess(p2);

  TBool done = EFalse;

  while (!done) {

    Random(); // randomize
    gameEngine->GameLoop();
    display.Update();
    if (controls.WasPressed(BUTTONQ)) {
      done = true;
    }

    if (controls.WasPressed(BUTTONA)) {
      printf("BUTTON A\n");
      soundPlayer.PlayMusic(STAGE_5_XM);
    }

    if (controls.WasPressed(BUTTON3)) {
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


    if (controls.WasPressed(BUTTONB)) {
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
