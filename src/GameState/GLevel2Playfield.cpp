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


void GLevel2Playfield::DrawScrolledBackground(BBitmap *aBitmap, TFloat aBackgroundOffsetH, TUint aVerticalOffset) {

  int canvasWidth     = gDisplay.renderBitmap->Width(),
      remainDrawWidth = canvasWidth, // Remaining width to draw, since we'll have to do multiple passes
      bgWidth         = aBitmap->Width(),
      bgHeight        = aBitmap->Height(),
      priorDrawWidth = 0;

  while (remainDrawWidth > 0) {
    int drawWidth;

    uint8_t *src = aBitmap->mPixels,
            *dest = gDisplay.renderBitmap->mPixels;

    //TODO: Figure out how to draw images LARGER than the canvas!
    if (remainDrawWidth == canvasWidth) {
      // 1st pass
      drawWidth = bgWidth - (int)aBackgroundOffsetH;
      dest += aVerticalOffset * 320;
      src  += (uint8_t)aBackgroundOffsetH;
    }
    else {
      //All other passes
      drawWidth = (bgWidth < remainDrawWidth) ? bgWidth : remainDrawWidth;
      dest += (aVerticalOffset * 320) + priorDrawWidth;
    }

    for (int y = 0; y < bgHeight; y++) {
      memcpy(dest, src, drawWidth);

      dest += canvasWidth;
      src += bgWidth;
    }

    priorDrawWidth += drawWidth;
    remainDrawWidth -= drawWidth;

    if (remainDrawWidth < 1) {
      return;
    }
  }
}
void GLevel2Playfield::DrawScrolledBackgroundWithTransparency(BBitmap *aBitmap, TFloat aBackgroundOffsetH, TUint aVerticalOffset) {

  uint8_t *src  = aBitmap->mPixels,
          *dest = gDisplay.renderBitmap->mPixels;

  int canvasWidth     = gDisplay.renderBitmap->Width(),
      remainDrawWidth = canvasWidth, // Remaining width to draw, since we'll have to do multiple passes
      bgWidth         = aBitmap->Width(),
      bgHeight        = aBitmap->Height(),
      srcIndex        = 0,
      destIndex       = 0;


  int priorDrawWidth = 0;

  while (remainDrawWidth > 0) {
    int drawWidth;

    //TODO: Figure out how to draw images LARGER than the canvas!
    if (remainDrawWidth == canvasWidth) {
      // 1st pass
      drawWidth = bgWidth - (int)aBackgroundOffsetH;
      destIndex = aVerticalOffset * 320;
      srcIndex  = (uint8_t)aBackgroundOffsetH;
    }
    else {
      //All other passes
      drawWidth = (bgWidth < remainDrawWidth) ? bgWidth : remainDrawWidth;
      destIndex = (aVerticalOffset * 320) + priorDrawWidth;
      srcIndex = 0;
    }


    for (int y = 0; y < bgHeight; y++) {
      for (int x = 0; x < drawWidth; x++) {
        uint8_t srcVal = src[srcIndex];

        if (srcVal != aBitmap->TransparentColor()) {
          dest[destIndex] = srcVal;
        }

        destIndex++;
        srcIndex++;

        if (destIndex > 76800) {
          return;
        }

      }

      srcIndex += bgWidth - drawWidth;
      if (remainDrawWidth == canvasWidth) {
        destIndex = (y + aVerticalOffset) * 320;
      }
      else {
        destIndex = ((y + aVerticalOffset) * 320) + priorDrawWidth;
      }
    }

    priorDrawWidth += drawWidth;
    remainDrawWidth -= drawWidth;

    if (remainDrawWidth < 1) {
      return;
    }
  }

}


void GLevel2Playfield::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);

  bgOffset0 += .01;
  if ((mBackground0->Width() - (int)bgOffset0) < 1) {
    bgOffset0 = 0;
  }

  bgOffset1 += .03;
  if ((mBackground1->Width() - (int)bgOffset1) < 1) {
    bgOffset0 = 0;
  }

  bgOffset2 += 2;
  if ((mBackground2->Width() - (int)bgOffset2) < 1) {
    bgOffset2= 0;
  }

}

void GLevel2Playfield::Render() {

//  memset(gDisplay.renderBitmap->mPixels, 0, 320*240);

  DrawScrolledBackground(mBackground0, bgOffset0, 0);

  DrawScrolledBackgroundWithTransparency(mBackground1, bgOffset1, 30);
  DrawScrolledBackgroundWithTransparency(mBackground2, bgOffset2, gDisplay.renderBitmap->Height() - mBackground2->Height() + 1);

//  mGameEngine->mGameBoard.Render();
}

