#include "Game.h"


//#define __XTENSA__
#ifndef __XTENSA__

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

uint8_t currentSong = 0,
        maxSongs = 3,
        currentSfx = 0,
        maxSfx = 9;

bool muted = false;


extern "C" void app_main() {
//  SeedRandom(time(ENull));
  display.Init();
  soundPlayer.Init();

  gResourceManager.LoadRaw(STAGE_2_XM, SONG_SLOT);
  BRaw *music = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.PlayMusic(music);


  gResourceManager.LoadRaw(SFX_BOSS_EXPLODE_WAV, 99);
  BRaw *effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 0, 0);

  gResourceManager.LoadRaw(SFX_ENEMY_EXPLODE_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 1, 0);

  gResourceManager.LoadRaw(SFX_ENEMY_FLYBY_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 2, 0);

  gResourceManager.LoadRaw(SFX_ENEMY_SHOOT_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 3, 0);

  gResourceManager.LoadRaw(SFX_NEXT_ATTRACT_CHAR_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 4, 0);

  gResourceManager.LoadRaw(SFX_NEXT_ATTRACT_CHAR_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 5, 0);

  gResourceManager.LoadRaw(SFX_NEXT_ATTRACT_SCREEN_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 6, 0);

  gResourceManager.LoadRaw(SFX_PLAYER_HIT_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 7, 0);

  gResourceManager.LoadRaw(SFX_PLAYER_SHOOT_WAV, 99);
  effect = gResourceManager.GetRaw(SONG_SLOT);
  soundPlayer.LoadEffect(effect, 8, 0);


//  printf("README size: %d\n", music->mSize);
//  printf("mData\n%.150s\n", (char *)music->mData);

//  printf("FILE SIZE = %i\n", music->mSize);
//
//  printf("%s\n", music->mData);
//
//  uint8_t *ptr = music->mData;
//
//  for (int i = 0; i < 8; i++) {
//    printf("%02X|\t", i);
//    for (int z = 1; z < 17; z++) {
//      printf("%02X", *ptr++);
//      if (z % 4 == 0) {
//        printf(" ");
//      }
//    }
//
//    printf("\n");
//  }



//
//  gResourceManager.LoadRaw(README_MD, README_SLOT);
//  BRaw *r = gResourceManager.GetRaw(README_SLOT);
//  printf("README size: %d\n", r->mSize);
//  printf("mData\n%.150s\n", (char *) r->mData);

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
#ifndef __XTENSA__
//    printf("%d %f\n", Random(10, 20), RandomFloat());
#endif
    Random(); // ranndomize
    gameEngine->GameLoop();
    display.Update();
    if (controls.WasPressed(BUTTONQ)) {
      done = true;
    }

    if (controls.WasPressed(BUTTONA)) {
      printf("BUTTONA\n");
      if (currentSong > maxSongs) {
        currentSong = 0;
      }
//      soundPlayer.PlayMusic(currentSong);
      currentSong++;
    }

    if (controls.WasPressed(BUTTON3)) {
      printf("BUTTON3\n");
      soundPlayer.MuteMusic(muted = !muted);
      printf("Muting ");
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
