// Created by jaygarcia on 10/23/18.
#include "Game.h"
#include "GLevel2Playfield.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif


GLevel2Playfield::GLevel2Playfield(GGameState *aGameEngine) {

  gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(CYBERPUNK0_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(CYBERPUNK1_BMP, BKG2_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(CYBERPUNK2_BMP, BKG3_SLOT, IMAGE_ENTIRE);

  mGameEngine = aGameEngine;
  mTextColor = 0;

  bgOffset0 = 0;
  bgOffset1 = 0;
  bgOffset2 = 0;

  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);
  mBackground1 = gResourceManager.GetBitmap(BKG2_SLOT);
  mBackground2 = gResourceManager.GetBitmap(BKG3_SLOT);

  mFrame = 0;

  printf("mBackground0 dimensions: %i x %i\n", mBackground0->Width(), mBackground0->Height());
  printf("mBackground1 dimensions: %i x %i\n", mBackground1->Width(), mBackground1->Height());
  printf("mBackground2 dimensions: %i x %i\n", mBackground2->Width(), mBackground2->Height());

}

GLevel2Playfield::~GLevel2Playfield()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
  delete mBackground0;
  delete mBackground1;
  delete mBackground2;

}

void GLevel2Playfield::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);

  gDisplay.renderBitmap->SetPalette(mBackground0, 0, 128);

  bgOffset0 += .01;
  bgOffset1 += .03;
  bgOffset2 += .05;
}

void GLevel2Playfield::Render() {

  //TODO:  @jaygarcia Clean up!
  
  uint8_t *src = mBackground0->mPixels,
          *dest = gDisplay.renderBitmap->mPixels;

  int canvasWidth = gDisplay.renderBitmap->Width(),
      bg0Height = mBackground0->Height(),
      bg0Width  = mBackground0->Width(),
      bg1Height = mBackground1->Height(),
      bg1Width  = mBackground1->Width(),
      bg2Height = mBackground2->Height(),
      bg2Width  = mBackground2->Width();


  /*** PAINT BACK MOST LAYER (mBackground0) ***/
  int drawWidth = bg0Width - (int)bgOffset0;

  if (drawWidth < 1) {
    drawWidth = 0;
    bgOffset0 = 0;
  }

  // paint initial block
  src += (uint8_t)bgOffset0;
  for (int y = 0; y < bg0Height; y++) {
    memcpy(dest, src, drawWidth);
    dest += canvasWidth;
    src += bg0Width;
  }

  // Second block
  // Reset the pointer. Can we do dest = 0?
  dest = gDisplay.renderBitmap->mPixels;
  src = mBackground0->mPixels;
  dest += drawWidth; // fast forward the pointer

  int widthDiff = 320 - drawWidth;

  for (int y = 0; y < bg0Height; y++) {
    memcpy(dest, src, widthDiff);
    dest += canvasWidth;
    src += bg0Width;
  }


  /*** PAINT MIDDLE LAYER (mBackground1) ***/
  int bg1StartHeight = 30;
  src = mBackground1->mPixels;
  dest = gDisplay.renderBitmap->mPixels;

  drawWidth = bg1Width - (uint8_t)bgOffset1;

  if (drawWidth < 1) {
    drawWidth = 0;
    bgOffset1 = 0;
  }

  int srcIndex = (uint8_t)bgOffset1;
  int destIndex = bg1StartHeight * 320;

  // paint initial block
  for (int y = 0; y < bg1Height; y++) {
    for (int x = 0; x < drawWidth; x++) {
      uint8_t srcVal = src[srcIndex];

      if (srcVal != mBackground0->TransparentColor()) {
        dest[destIndex] = srcVal;
      }

      destIndex++;
      srcIndex++;
    }

    srcIndex += bg1Width - drawWidth;
    destIndex = (y + bg1StartHeight) * 320;
  }



  // Second block
  srcIndex = 0;
  int secondDrawWidth = 320 - drawWidth;
  destIndex = drawWidth + (bg1StartHeight * 320); // fast forward the pointer

  for (int y = 0; y < bg1Height; y++) {
    for (int x = 0; x < secondDrawWidth; x++) {
      uint8_t srcVal = src[srcIndex];

      if (srcVal != mBackground0->TransparentColor()) {
        dest[destIndex] = srcVal;
      }

      destIndex++;
      srcIndex++;
    }

    srcIndex += bg1Width - secondDrawWidth;
    destIndex = ((y + bg1StartHeight) * 320) + drawWidth;
  }





  /*** PAINT LAST LAYER (mBackground2) ***/
  int bg2StartHeight = 240 - bg2Height + 1;
  src = mBackground2->mPixels;

  drawWidth = bg1Width - (uint8_t)bgOffset2;

  if (drawWidth < 1) {
    drawWidth = 0;
    bgOffset2 = 0;
  }

  srcIndex = (uint8_t)bgOffset2;
  destIndex = bg2StartHeight * 320;

  // paint initial block
  for (int y = 0; y < bg2Height; y++) {
    for (int x = 0; x < drawWidth; x++) {
      uint8_t srcVal = src[srcIndex];

      if (srcVal != mBackground1->TransparentColor()) {
        dest[destIndex] = srcVal;
      }

      destIndex++;
      srcIndex++;
    }

    srcIndex += bg2Width - drawWidth;
    destIndex = (y + bg2StartHeight) * 320;
  }


  // Second block
  srcIndex = 0;
  secondDrawWidth = 320 - drawWidth;
  destIndex = drawWidth + (bg2StartHeight * 320); // fast forward the pointer

  for (int y = 0; y < bg2Height; y++) {
    for (int x = 0; x < secondDrawWidth; x++) {
      uint8_t srcVal = src[srcIndex];

      if (srcVal != mBackground1->TransparentColor()) {
        dest[destIndex] = srcVal;
      }

      destIndex++;
      srcIndex++;
    }

    srcIndex += bg2Width - secondDrawWidth;
    destIndex = ((y + bg2StartHeight) * 320) + drawWidth;
  }



  mGameEngine->mGameBoard.Render();
}

