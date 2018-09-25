#include "GameEngine.h"
#include "GGameEngine.h"
#include "GResources.h"
#include <stdio.h>
#include <unistd.h>

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
    mSprite = new BSprite(0, PLAYER_SLOT, 0);
    mSprite->x = mSprite->y = 0;
    gameEngine->AddSprite(mSprite);
  }

  TBool RunBefore() {
    mBitmap = display.displayBitmap;
    if(mPropToggle) {
      mBitmap->SetColor(200, 151, 151, 151);
      mBitmap->SetColor(201, 238, 238, 238);
      mBitmap->SetColor(202, 255, 0, 0);
      mBitmap->SetColor(203, 255, 255, 0);
    } else {
      mBitmap->SetColor(200, 238, 238, 238);
      mBitmap->SetColor(201, 151, 151, 151);
      mBitmap->SetColor(202, 255, 255, 0);
      mBitmap->SetColor(203, 255, 0, 0);
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

  BBitmap *mBitmap;
  TBool mPropToggle;
  BSprite *mSprite;
};


class GDemoProcess2 : public BProcess {
public:
  GDemoProcess2(TInt x, TInt y, TInt i) : BProcess(PTYPE_USER) {
    mSprite = new BSprite(0, PLAYER_SLOT, i);
    mSprite->x = x;
    mSprite->y = y;
    gameEngine->AddSprite(mSprite);
  }

  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    return ETrue;
  }

  BSprite *mSprite;
};

BViewPort *viewPort;

extern "C" void app_main() {
  display.Init();
  resourceManager.LoadBitmap(PLAYERNEW_BMP, PLAYER_SLOT, IMAGE_16x16);
  BBitmap *b = resourceManager.GetBitmap(PLAYER_SLOT);
  display.SetPalette(b);
  // resourceManager.LoadBitmap(BKG3_BMP, BKG_SLOT, IMAGE_ENTIRE);
  // b = resourceManager.GetBitmap(BKG_SLOT);
//  display.SetPalette(b);

  viewPort = new BViewPort();
  viewPort->Offset(32, 32);

  TRect clipRect;
  clipRect.Set(0, 0, 288, 210);
  viewPort->SetRect(clipRect);

  gameEngine = new GGameEngine(viewPort);

  // auto *p = new GDemoProcess();
  // gameEngine->AddProcess(p);
  for (TInt x = 0; x < 14; x++) {
    for (TInt y = 0; y < 14; y++) {
      auto *p2 = new GDemoProcess2(x*16 + 2*x, y*16 +2*y, (x + y + 1) % 2 == 0 ? 1 : 0);
      gameEngine->AddProcess(p2);
    }
  }

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
  }

  printf("Exiting\n");
}

#ifndef __XTENSA__

int main() {
  app_main();
  return 0;
}

#endif
