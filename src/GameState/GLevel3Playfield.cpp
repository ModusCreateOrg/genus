//
// Created by mschwartz on 10/21/18.
//

#include "Game.h"
#include "GLevel3Playfield.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif

//int8_t *xOffset;

//int8_t *yComp;
//
//
//GLevel3Playfield::GLevel3Playfield(GGameState *aGameEngine) {
//  gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
//  gResourceManager.LoadBitmap(UNDER_WATER_BMP, BKG_SLOT, IMAGE_ENTIRE);
//
//  gDisplay.renderBitmap->SetPalette(mBackground, 0, 128);
//
//  mGameEngine = aGameEngine;
//  mTextColor = 0;
//  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
//  mFrame = 0; // TODO: mFrame could be TFloat
//
//
////  xOffset = (int8_t *)AllocMem(320, MEMF_SLOW);
//  mXComp   = (int8_t *)AllocMem(320, MEMF_SLOW);
//  mYOffset = (int8_t *)AllocMem(240, MEMF_SLOW);
////  yComp   = (int8_t *)AllocMem(240, MEMF_SLOW);
//
//}
//
//GLevel3Playfield::~GLevel3Playfield()  {
//  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
//  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
//
//  delete mYOffset;
//  delete mXComp;
//}
//
//void GLevel3Playfield::Animate() {
//  mTextColor += 1;
//  mTextColor %= 64;
//  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);
//
//  // This block will setup x and y offsets
//  mFrame++;
//  for (int x = 0; x < 320; x++) {
////    xOffset[x] = sin(mFrame * 0.15 + x * 0.06) * 4;
//    mXComp[x] = sin(mFrame * 0.11 + x * 0.12) * 3.0f;
//  }
//
//  for (int y = 0; y < 240; y++) {
//    mYOffset[y] = sin(mFrame * 0.1 + y * 0.05) * 2.0f;
////    yComp[y] = sin(mFrame * 0.07 + y * 0.15) * 4;
//  }
//
//}
//
//void GLevel3Playfield::Render() {
//  uint8_t *src = mBackground->mPixels,
//          *dest = gDisplay.renderBitmap->mPixels;
//
//
////  memset(mBackground->mPixels, 0, 320 * 240);
//  int srcIndex = 8,
//          destIndex = 0;
//
//  for (uint8_t y = 0; y < 240; y++) {
//    for (int x = 0; x < 320; x++) {
//      dest[destIndex] = src[srcIndex + mYOffset[y] + mXComp[x]];
//
//      srcIndex++;
//      destIndex++;
//    }
//
//    srcIndex += 16;
//  }
//
//  mGameEngine->mGameBoard.Render();
//}
