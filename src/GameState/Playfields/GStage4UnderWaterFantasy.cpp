#include "GStage4UnderWaterFantasy.h"
#include "Game.h"
#include "PrecalcSines.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif






GStage4UnderWaterFantasy::GStage4UnderWaterFantasy(GGameState *aGameEngine) {
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


  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);
//  mBackground1 = gResourceManager.GetBitmap(BKG2_SLOT);
//  mBackground2 = gResourceManager.GetBitmap(BKG3_SLOT);

  mXSinIndex = 0;
  mYSinIndex = 0;

  mXComp   = (int8_t *)AllocMem(320, MEMF_SLOW);
  mYOffset = (int8_t *)AllocMem(240, MEMF_SLOW);
}

GStage4UnderWaterFantasy::~GStage4UnderWaterFantasy()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  // gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  // gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);

  FreeMem(mYOffset);
  FreeMem(mXComp);
  delete mCanvasBitmap;
}



void GStage4UnderWaterFantasy::Animate() {
//  mTextColor += 1;
//  mTextColor %= 64;
//  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);

  // This block will setup x and y offsets
  int workingXSinIndex = mXSinIndex;
  for (int x = 0; x < 320; x++) {
//    xOffset[x] = sin(mFrame * 0.15 + x * 0.06) * 4;
//    mXComp[x] = sin(mFrame * 0.11 + x * 0.12) * 3.0f;

    mXComp[x] = xSin[workingXSinIndex];
    workingXSinIndex++;
    if (workingXSinIndex > 319) {
      workingXSinIndex = 0;
    }
  }

  int workingYSinIndex = mYSinIndex;
  for (int y = 0; y < 240; y++) {
//    mYOffset[y] = sin(mFrame * 0.1 + y * 0.05) * 2.0f;
//    yComp[y] = sin(mFrame * 0.07 + y * 0.15) * 4;

    mYOffset[y] = ySin[workingYSinIndex];
    workingYSinIndex++;
    if (workingYSinIndex > 239) {
      workingYSinIndex = 0;
    }
  }

  mXSinIndex++;
  if (mXSinIndex > 319) {
    mXSinIndex = 0;
  }

  mYSinIndex++;
  if (mYSinIndex > 239) {
    mYSinIndex = 0;
  }

}



// Experimental scrolling background with a custom canvas. Not used as of this time.
void GStage4UnderWaterFantasy::DrawScrolledBackground(BBitmap *aBitmap, TFloat aOffsetX, TUint aVerticalOffset, TBool aDrawTransparent, BBitmap *aCanvasBitmap) {

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

void GStage4UnderWaterFantasy::Render() {

//  memset(mCanvasBitmap->mPixels, 0,  mCanvasBitmap->Height() *  mCanvasBitmap->Width()); // debug purposes
//  DrawScrolledBackground(mBackground0, bgOffset0, 0, EFalse, mCanvasBitmap);
//  DrawScrolledBackground(mBackground1, bgOffset1, 95, ETrue, mCanvasBitmap);
//  DrawScrolledBackground(mBackground2, bgOffset2, mCanvasBitmap->Height() - mBackground2->Height() - 15, ETrue, mCanvasBitmap);

  TUint8 *src = mBackground0->GetPixels(),
          *dest = gDisplay.renderBitmap->GetPixels();

  int srcIndex = 8,
      destIndex = 0;


  for (TUint8 y = 0; y < 240; y++) {
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

