//
// Created by Jesus Garcia on 11/5/18.
//


#include "GLevelUnderWaterFantasy.h"
#include "Game.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif






GLevelUnderWaterFantasy::GLevelUnderWaterFantasy(GGameState *aGameEngine) {

  gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(UNDER_WATER_FANTASY_BMP, BKG_SLOT, IMAGE_ENTIRE);
//  gResourceManager.LoadBitmap(UNDER_WATER_FANTASY0_BMP, BKG_SLOT, IMAGE_ENTIRE);
//  gResourceManager.LoadBitmap(UNDER_WATER_FANTASY1_BMP, BKG2_SLOT, IMAGE_ENTIRE);
//  gResourceManager.LoadBitmap(UNDER_WATER_FANTASY2_BMP, BKG3_SLOT, IMAGE_ENTIRE);


  mCanvasBitmap = new BBitmap(336, 256, 8, MEMF_SLOW);
//  mViewport = new BViewPort();
//  TRect viewportRect = ;
//  mViewport->SetRect(TRect(0, 0, 336, 256));

  mGameEngine = aGameEngine;
  mTextColor = 0;

  bgOffset0 = 0;
  bgOffset1 = 0;
  bgOffset2 = 0;

  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);
//  mBackground1 = gResourceManager.GetBitmap(BKG2_SLOT);
//  mBackground2 = gResourceManager.GetBitmap(BKG3_SLOT);

  mFrame   = 0.0f;
  mXComp   = (int8_t *)AllocMem(320, MEMF_SLOW);
  mYOffset = (int8_t *)AllocMem(240, MEMF_SLOW);
}

GLevelUnderWaterFantasy::~GLevelUnderWaterFantasy()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  // gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  // gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);

  delete mYOffset;
  delete mXComp;
}



void GLevelUnderWaterFantasy::Animate() {
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

//  // Base background
//  bgOffset0 += .005;
//  if ((int)bgOffset0 >= mBackground0->Width()) {
//    bgOffset0= 0;
//  }
//
//  bgOffset1 += .008;
//  if ((int)bgOffset1 >= mBackground1->Width()) {
//    bgOffset1 = 0;
//  }
//
//  bgOffset2 += .5;// .01;
//  if ((int)bgOffset2 >= mBackground2->Width()) {
//    bgOffset2 = 0;
//  }


}





// Experimental scrolling background with a custom canvas. Not used as of this time.
void GLevelUnderWaterFantasy::DrawScrolledBackground(BBitmap *aBitmap, TFloat aOffsetX, TUint aVerticalOffset, TBool aDrawTransparent, BBitmap *aCanvasBitmap) {

  int intOffsetX = (int)aOffsetX,
      canvasWidth = aCanvasBitmap->Width(),
      remainDrawWidth = canvasWidth, // Remaining width to draw, since we'll have to do multiple passes
      bgWidth = aBitmap->Width(),
      priorDrawWidth = 0;


  int imgWidthDelta = bgWidth - intOffsetX;

  // Background is too big for the canvas, so just draw the full canvas width and be done!
//  if (imgWidthDelta >= canvasWidth) {
//    TRect rect = TRect(intOffsetX, 0, bgWidth - 1, aBitmap->Height() - 1);
//
//    if (aDrawTransparent) {
//      aCanvasBitmap->DrawBitmapTransparent(mViewport, aBitmap, rect, 0, aVerticalOffset);
//    }
//    else {
//      aCanvasBitmap->DrawBitmap(mViewport, aBitmap, rect, 0, aVerticalOffset);
//    }
//    return;
//  }


  while (remainDrawWidth > 0) {
    int drawWidth = 0;

    // Background is too big for the canvas
    if (bgWidth > canvasWidth) {
      if (remainDrawWidth == canvasWidth) {
        drawWidth = imgWidthDelta;
        TRect rect = TRect(intOffsetX, 0, bgWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          aCanvasBitmap->DrawBitmapTransparent(mViewport, aBitmap, rect, 0, aVerticalOffset);
        }
        else {
          aCanvasBitmap->DrawBitmap(mViewport, aBitmap, rect, 0, aVerticalOffset);
        }

      }
      else {
        drawWidth = canvasWidth - priorDrawWidth;
        TRect rect = TRect(0, 0, drawWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          aCanvasBitmap->DrawBitmapTransparent(mViewport, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
        else {
          aCanvasBitmap->DrawBitmap(mViewport, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
      }
    }
    else { // Backgrounds that are too small for the canvas
      if (remainDrawWidth == canvasWidth) {
        drawWidth = bgWidth - intOffsetX;
        TRect rect = TRect(intOffsetX, 0, bgWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          aCanvasBitmap->DrawBitmapTransparent(mViewport, aBitmap, rect, 0, aVerticalOffset);
        }
        else {
          aCanvasBitmap->DrawBitmap(mViewport, aBitmap, rect, 0, aVerticalOffset);
        }
      }
      else {
        drawWidth = (remainDrawWidth > bgWidth) ? bgWidth : remainDrawWidth;
        TRect rect = TRect(0, 0, drawWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          aCanvasBitmap->DrawBitmapTransparent(mViewport, aBitmap, rect,  priorDrawWidth, aVerticalOffset);
        }
        else {
          aCanvasBitmap->DrawBitmap(mViewport, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
      }
    }


    if (drawWidth == 0) {
      return;
    }

    priorDrawWidth += drawWidth;
    remainDrawWidth -= drawWidth;

    if (remainDrawWidth < 1) {
      return;
    }
  }
}

void GLevelUnderWaterFantasy::Render() {

//  memset(mCanvasBitmap->mPixels, 0,  mCanvasBitmap->Height() *  mCanvasBitmap->Width()); // debug purposes
//  DrawScrolledBackground(mBackground0, bgOffset0, 0, EFalse, mCanvasBitmap);
//  DrawScrolledBackground(mBackground1, bgOffset1, 95, ETrue, mCanvasBitmap);
//  DrawScrolledBackground(mBackground2, bgOffset2, mCanvasBitmap->Height() - mBackground2->Height() - 15, ETrue, mCanvasBitmap);

  uint8_t *src = mBackground0->GetPixels(),
          *dest = gDisplay.renderBitmap->GetPixels();

  int srcIndex = 8,
      destIndex = 0;


  for (uint8_t y = 0; y < 240; y++) {
    for (int x = 0; x < 320; x++) {
      dest[destIndex] = src[srcIndex + mYOffset[y] + mXComp[x]];

      srcIndex++;
      destIndex++;
    }


//    memcpy(dest, src, DISPLAY_WIDTH);
//    dest += gDisplay.renderBitmap->Width();
//    src +=  mCanvasBitmap->Width();
//    destIndex += 240;
    srcIndex += 16;
  }


  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}

