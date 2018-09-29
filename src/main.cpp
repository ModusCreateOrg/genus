#include "GameEngine.h"
#include "GGameEngine.h"
#include "GResources.h"
#include <stdio.h>
#include <unistd.h>


//#define __XTENSA__
#ifndef __XTENSA__

#include "SDL2/SDL.h"

#endif

#define FRAMERATE 30

GGameEngine *gameEngine;

#define DELTA_V .5

class GDemoProcess : public BProcess {
public:
  GDemoProcess() : BProcess(PTYPE_USER) {
    mPropToggle = EFalse;
    mSprite     = new BSprite(0, PLAYER_SLOT, 0);
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

  TBool   mPropToggle;
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

uint8_t currentSong = 0,
        maxSongs = 3,
        currentSfx = 0,
        maxSfx = 9;

bool muted = false;

#define SONG_SLOT 0

extern "C" void app_main() {
  display.Init();
  soundPlayer.Init();

  resourceManager.LoadRaw(STAGE_2_XM, SONG_SLOT);
  BRaw *music = resourceManager.GetRaw(README_SLOT);
//  printf("README size: %d\n", music->mSize);
//  printf("mData\n%.150s\n", (char *)music->mData);
  soundPlayer.PlayMusic(music);


  resourceManager.LoadRaw(README_MD, README_SLOT);
  BRaw *r = resourceManager.GetRaw(README_SLOT);
  printf("README size: %d\n", r->mSize);
  printf("mData\n%.150s\n", (char *)r->mData);

  resourceManager.LoadBitmap(PLAYERNEW_BMP, PLAYER_SLOT, IMAGE_32x32);
  BBitmap *b = resourceManager.GetBitmap(PLAYER_SLOT);
  display.SetPalette(b);
  resourceManager.LoadBitmap(BKG3_BMP, BKG_SLOT, IMAGE_ENTIRE);
  b = resourceManager.GetBitmap(BKG_SLOT);
//  display.SetPalette(b);



  viewPort = new BViewPort();
  viewPort->Offset(50, 0);
  viewPort->SetRect(b->Dimensions());

  gameEngine = new GGameEngine(viewPort);

  auto *p = new GDemoProcess();
  gameEngine->AddProcess(p);
  auto *p2 = new GDemoProcess2();
  gameEngine->AddProcess(p2);

  TUint32 now  = Milliseconds();
  TUint32 next = now + 1000 / FRAMERATE;

  TBool done = EFalse;

  while (!done) {
    while (now < next) now = Milliseconds();
    next = next + 1000 / FRAMERATE;
    gameEngine->GameLoop();
    display.Update();
    if (controls.WasPressed(BUTTONQ)) {
      done = true;
    }

    if (controls.WasPressed(BUTTONA)) {
      if (currentSong > maxSongs) {
        currentSong = 0;
      }
//      soundPlayer.PlayMusic(currentSong);
      currentSong++;


    }

    if (controls.WasPressed(BUTTON3)) {
      soundPlayer.MuteMusic(muted = !muted);
    }

    if (controls.WasPressed(BUTTONB)) {
      printf("BUTTON 3\n"); fflush(stdout);
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
