// Created by jaygarcia on 10/23/18.
#include "Game.h"
#include "GLevelCyberpunk.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif


/*************************************************************************/


class BuildingLights : public BProcess {
public:
  BuildingLights() : BProcess() {
    mTimer = TIME;
    mColor = COLOR1;
  }

public:
  TBool RunBefore() {
    if (--mTimer < 0) {
      mTimer = TIME;
      mColor = mColor == COLOR1 ? COLOR2 : COLOR1;
    }
    TRGB color(mColor);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX, color);
    return ETrue;
  }

  TBool RunAfter() {
    return ETrue;
  }

private:
  TInt       mTimer;
  const TInt TIME                  = 2 * 30;

  TUint32              mColor;
  static const TInt16  COLOR_INDEX = 36;
  static const TUint32 COLOR1      = 0x7b315a;
  static const TUint32 COLOR2      = 0x182139;
};

/*************************************************************************/

class TowersLights : public BProcess {
public:
  TowersLights() : BProcess() {
    mTimer  = TIME;
    mColor1 = COLOR1;
    mColor2 = COLOR2;
  }

public:
  TBool RunBefore() {
    if (--mTimer < 0) {
      mTimer  = TIME;
      mColor1 = mColor1 == COLOR1 ? COLOR2 : COLOR1;
      mColor2 = mColor2 == COLOR1 ? COLOR2 : COLOR1;
    }
    TRGB color1(mColor1);
    TRGB color2(mColor2);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX1, color1);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX2, color2);
    return ETrue;
  }

  TBool RunAfter() {
    return ETrue;
  }

private:
  TInt       mTimer;
  const TInt TIME                   = 3 * 30;

  TUint32              mColor1, mColor2;
  static const TInt16  COLOR_INDEX1 = 37;
  static const TInt16  COLOR_INDEX2 = 38;
  static const TUint32 COLOR1       = 0xB36930;
  static const TUint32 COLOR2       = 0x291831;
};

/*************************************************************************/

class ModusNeonLamp : public BProcess {
public:
  ModusNeonLamp() : BProcess() {
    mTimer  = TIME1;
    mColor1 = COLOR1;
    mColor2 = COLOR3;
  }

public:
  TBool RunBefore() {
    if (--mTimer < 0) {
      mColor1 = mColor1 == COLOR1 ? COLOR2 : COLOR1;
      mColor2 = mColor2 == COLOR3 ? COLOR4 : COLOR3;
      mTimer  = mColor1 == COLOR1 ? TIME1 : TIME2;
    }
    TRGB color1(mColor1);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX1, color1);
    TRGB color2(mColor2);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX2, color2);
    return ETrue;
  }

  TBool RunAfter() {
    return ETrue;
  }

private:
  TInt       mTimer;
  const TInt TIME1                  = 10 * 30;  // 10 seconds
  const TInt TIME2                  = 15;       // .5 seconds

  TUint32              mColor1, mColor2;
  static const TInt16  COLOR_INDEX1 = 39;
  static const TInt16  COLOR_INDEX2 = 40;
  static const TUint32 COLOR1       = 0xA52131;
  static const TUint32 COLOR2       = 0x180810;
  static const TUint32 COLOR3       = 0xB55218;
  static const TUint32 COLOR4       = 0x180810;
};

/*************************************************************************/

class BottleNeonLamp : public BProcess {
public:
  BottleNeonLamp() : BProcess() {
    mTimer  = TIME1;
    mColor1 = COLOR1;
    mColor2 = COLOR3;
    mColor3 = COLOR5;
    mColor4 = COLOR7;
  }

public:
  TBool RunBefore() {
    if (--mTimer < 0) {
      mColor1 = mColor1 == COLOR1 ? COLOR2 : COLOR1;
      mColor2 = mColor2 == COLOR3 ? COLOR4 : COLOR3;
      mColor3 = mColor3 == COLOR5 ? COLOR6 : COLOR5;
      mColor4 = mColor4 == COLOR7 ? COLOR8 : COLOR7;
      mTimer  = mColor1 == COLOR1 ? TIME1 : TIME2;
    }
    TRGB color(mColor1);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX1, color);
    color.Set(mColor2);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX2, color);
    color.Set(mColor3);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX3, color);
    color.Set(mColor4);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX4, color);
    return ETrue;
  }

  TBool RunAfter() {
    return ETrue;
  }

private:
  TInt       mTimer;
  const TInt TIME1                  = 5 * 30; // 5 seconds
  const TInt TIME2                  = 1 * 30; //  1 second

  TUint32              mColor1, mColor2, mColor3, mColor4;
  static const TInt16  COLOR_INDEX1 = 41;
  static const TInt16  COLOR_INDEX2 = 42;
  static const TInt16  COLOR_INDEX3 = 43;
  static const TInt16  COLOR_INDEX4 = 44;
  static const TUint32 COLOR1       = 0x180810;
  static const TUint32 COLOR2       = 0x080008;
  static const TUint32 COLOR3       = 0x4A1018;
  static const TUint32 COLOR4       = 0x080008;
  static const TUint32 COLOR5       = 0xA52131;
  static const TUint32 COLOR6       = 0x4A1018;
  static const TUint32 COLOR7       = 0xB55218;
  static const TUint32 COLOR8       = 0x4A1018;
};

/*************************************************************************/

class ModusEasterEgg : public BProcess {
public:
  ModusEasterEgg() : BProcess() {
    mTimer  = TIME1;
    mColor1 = COLOR1;
    mColor2 = COLOR3;
    mColor3 = COLOR4;
  }

public:
  TBool RunBefore() {
    if (--mTimer < 0) {
      mColor1 = mColor1 == COLOR1 ? COLOR2 : COLOR1;
      mColor2 = mColor2 == COLOR3 ? COLOR4 : COLOR3;
      mColor3 = mColor3 == COLOR5 ? COLOR6 : COLOR5;
      mTimer  = mColor1 == COLOR1 ? TIME1 : TIME2;
    }
    TRGB color(mColor1);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX1, color);
    color.Set(mColor2);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX3, color);
    color.Set(mColor3);
    gDisplay.renderBitmap->SetColor(COLOR_INDEX4, color);
    return ETrue;
  }

  TBool RunAfter() {
    return ETrue;
  }

private:
  TInt       mTimer;
  const TInt TIME1                  = 20 * 30; // 5 seconds
  const TInt TIME2                  = 2 * 30; //  1 second

  TUint32              mColor1, mColor2, mColor3, mColor4;
  static const TInt16  COLOR_INDEX1 = 45;
  static const TInt16  COLOR_INDEX2 = 46; // no color change
  static const TInt16  COLOR_INDEX3 = 47;
  static const TInt16  COLOR_INDEX4 = 48;
  static const TUint32 COLOR1       = 0x213942;
  static const TUint32 COLOR2       = 0x21524A;
  static const TUint32 COLOR3       = 0x21524A;
  static const TUint32 COLOR4       = 0x213942;
  static const TUint32 COLOR5       = 0x213942;
  static const TUint32 COLOR6       = 0x21524A;
};

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

GLevelCyberpunk::GLevelCyberpunk(GGameState *aGameEngine) {

  // Am leaving scrolling code in place until we find a better solution to perf issues.
#ifdef STATIC_GAME_BACKGROUNDS
  gResourceManager.LoadBitmap(CYBERPUNK_STATIC_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);
#else
  gResourceManager.LoadBitmap(CYBERPUNK0_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(CYBERPUNK1_BMP, BKG2_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(CYBERPUNK2_BMP, BKG3_SLOT, IMAGE_ENTIRE);
  bgOffset0 = 0;
  bgOffset1 = 0;
  bgOffset2 = 0;

  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);
  mBackground1 = gResourceManager.GetBitmap(BKG2_SLOT);
  mBackground2 = gResourceManager.GetBitmap(BKG3_SLOT);

  printf("mBackground0 dimensions: %i x %i\n", mBackground0->Width(), mBackground0->Height());
  printf("mBackground1 dimensions: %i x %i\n", mBackground1->Width(), mBackground1->Height());
  printf("mBackground2 dimensions: %i x %i\n", mBackground2->Width(), mBackground2->Height());
#endif

  mGameEngine = aGameEngine;
  mTextColor  = 0;

  mBuildingLightsProcess = new BuildingLights();
  mTowerLightsProcess = new TowersLights();
  mModusNeonLampProcess = new ModusNeonLamp();
  mBottleNeonLampProcess = new BottleNeonLamp();
  mModusEasterEggProcess = new ModusEasterEgg();

  mGameEngine->AddProcess(mBuildingLightsProcess);
  mGameEngine->AddProcess(mTowerLightsProcess);
  mGameEngine->AddProcess(mModusNeonLampProcess);
  mGameEngine->AddProcess(mBottleNeonLampProcess);
  mGameEngine->AddProcess(mModusEasterEggProcess);
}

GLevelCyberpunk::~GLevelCyberpunk()  {
#ifdef STATIC_GAME_BACKGROUNDS
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
#else
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);

  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
#endif

  // Stop all processes
  mBuildingLightsProcess->Remove();
  mTowerLightsProcess->Remove();
  mModusNeonLampProcess->Remove();
  mBottleNeonLampProcess->Remove();
  mModusEasterEggProcess->Remove();

  delete mBuildingLightsProcess;
  delete mTowerLightsProcess;
  delete mModusNeonLampProcess;
  delete mBottleNeonLampProcess;
  delete mModusEasterEggProcess;
}


void GLevelCyberpunk::Animate() {
#ifndef STATIC_GAME_BACKGROUNDS
  bgOffset0 += .01;
  if ((int)bgOffset0 >= mBackground0->Width()) {
    bgOffset0= 0;
  }

  bgOffset1 += .025;
  if ((int)bgOffset1 >= mBackground1->Width()) {
    bgOffset1 = 0;
  }

  bgOffset2 += .08;
  if ((int)bgOffset2 >= mBackground2->Width()) {
    bgOffset2 = 0;
  }
#endif

}

void GLevelCyberpunk::Render() {

//  memset(gDisplay.renderBitmap->GetPixels(), 25, 320 * 135);
#ifdef STATIC_GAME_BACKGROUNDS
  gDisplay.renderBitmap->CopyPixels(mBackground0);
#else
  DrawScrolledBackground(mBackground0, bgOffset0, 0);
  DrawScrolledBackground(mBackground1, bgOffset1, 30, ETrue);
  DrawScrolledBackground(mBackground2, bgOffset2, gDisplay.renderBitmap->Height() - mBackground2->Height() + 1, ETrue); // Same with this code.
#endif

  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}

