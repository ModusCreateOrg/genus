//
// Created by mschwartz on 10/21/18.
//

#include "Game.h"
#include "GLevel1Playfield.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif

//static int8_t xOffset[320], yOffset[240];
//static int8_t xComp[320], yComp[240];

//int8_t *xOffset;
int8_t *yOffset;
int8_t *xComp;
//int8_t *yComp;


GLevel1Playfield::GLevel1Playfield(GGameState *aGameEngine) {
  mGameEngine = aGameEngine;
  mTextColor = 0;
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  mFrame = 0;


//  xOffset = (int8_t *)AllocMem(320, MEMF_SLOW);
  xComp   = (int8_t *)AllocMem(320, MEMF_SLOW);
  yOffset = (int8_t *)AllocMem(240, MEMF_SLOW);
//  yComp   = (int8_t *)AllocMem(240, MEMF_SLOW);

}

GLevel1Playfield::~GLevel1Playfield()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GLevel1Playfield::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);

  // This block will setup x and y offsets
  mFrame++;
  for (int x = 0; x < 320; x++) {
//    xOffset[x] = sin(mFrame * 0.15 + x * 0.06) * 4;
    xComp[x] = sin(mFrame * 0.11 + x * 0.12) * 3;
  }

  for (int y = 0; y < 240; y++) {
    yOffset[y] = sin(mFrame * 0.1 + y * 0.05) * 2;
//    yComp[y] = sin(mFrame * 0.07 + y * 0.15) * 4;
  }

  gDisplay.renderBitmap->SetPalette(mBackground, 0, 128);
}

void GLevel1Playfield::Render() {
//  gDisplay.renderBitmap->CopyPixels(mBackground);


  uint8_t *src = mBackground->mPixels,
          *dest = gDisplay.renderBitmap->mPixels;


//  memset(mBackground->mPixels, 0, 320 * 240);
  int srcIndex = 8,
      destIndex = 0;

  for (uint8_t y = 0; y < 240; y++) {
    for (int x = 0; x < 320; x++) {

//      dest[destIndex] = src[srcIndex];
      dest[destIndex] = src[srcIndex + yOffset[y] + xComp[x]];

      srcIndex++;
      destIndex++;
    }

    srcIndex += 16;
  }

  mGameEngine->mGameBoard.Render();
}

