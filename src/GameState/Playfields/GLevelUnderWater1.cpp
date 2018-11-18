#include "Game.h"
#include "GLevelUnderWater1.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif

//int8_t *xOffset;
//
//int8_t *yComp;


GLevelUnderWater1::GLevelUnderWater1(GGameState *aGameEngine) {
  gResourceManager.LoadBitmap(UNDER_WATER_BMP, BKG_SLOT, IMAGE_ENTIRE);

//  gDisplay.renderBitmap->SetPalette(mBackground, 0, 128);

  mGameEngine = aGameEngine;
  mTextColor = 0;
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  mFrame = 0; // TODO: mFrame could be TFloat


//  xOffset = (int8_t *)AllocMem(320, MEMF_SLOW);
  mXComp   = (int8_t *)AllocMem(320, MEMF_SLOW);
  mYOffset = (int8_t *)AllocMem(240, MEMF_SLOW);
//  yComp   = (int8_t *)AllocMem(240, MEMF_SLOW);

}

GLevelUnderWater1::~GLevelUnderWater1()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);

  delete mYOffset;
  delete mXComp;
}

void GLevelUnderWater1::Animate() {
//  mTextColor += 1;
//  mTextColor %= 64;
//  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);

  // This block will setup x and y offsets
  mFrame++;
  for (int x = 0; x < 320; x++) {
//    xOffset[x] = sin(mFrame * 0.15 + x * 0.06) * 4;
    mXComp[x] = sin(mFrame * 0.11 + x * 0.12) * 3.0f;
  }

  for (int y = 0; y < 240; y++) {
    mYOffset[y] = sin(mFrame * 0.1 + y * 0.05) * 2.0f;
//    yComp[y] = sin(mFrame * 0.07 + y * 0.15) * 4;
  }

}

void GLevelUnderWater1::Render() {
  uint8_t *src = mBackground->GetPixels(),
          *dest = gDisplay.renderBitmap->GetPixels();

  int srcIndex = 8,
      destIndex = 0;

  for (uint8_t y = 0; y < 240; y++) {
    for (int x = 0; x < 320; x++) {
      dest[destIndex] = src[srcIndex + mYOffset[y] + mXComp[x]];

      srcIndex++;
      destIndex++;
    }

    srcIndex += 16;
  }

  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}
