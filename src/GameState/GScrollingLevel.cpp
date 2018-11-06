//
// Created by Jesus Garcia on 10/28/18.
//

#include "GScrollingLevel.h"





void GScrollingLevel::DrawScrolledBackground(BBitmap *aBitmap, TFloat aOffsetX, TUint aVerticalOffset, TBool aDrawTransparent) {

  int intOffsetX = (int)aOffsetX,
      canvasWidth = gDisplay.GetRenderBitmap()->Width(),
      remainDrawWidth = canvasWidth, // Remaining width to draw, since we'll have to do multiple passes
      bgWidth = aBitmap->Width(),
      priorDrawWidth = 0;


  int imgWidthDelta = bgWidth - intOffsetX;

  // Background is too big for the canvas, so just draw the full canvas width and be done!
  if (imgWidthDelta >= canvasWidth) {
    TRect rect = TRect(intOffsetX, 0, bgWidth - 1, aBitmap->Height() - 1);

    if (aDrawTransparent) {
      gDisplay.GetRenderBitmap()->DrawBitmapTransparent(ENull, aBitmap, rect, 0, aVerticalOffset);
    }
    else {
      gDisplay.GetRenderBitmap()->DrawBitmap(ENull, aBitmap, rect, 0, aVerticalOffset);
    }
    return;
  }


  while (remainDrawWidth > 0) {
    int drawWidth = 0;

    // Background is too big for the canvas
    if (bgWidth > canvasWidth) {
      if (remainDrawWidth == canvasWidth) {
        drawWidth = imgWidthDelta;
        TRect rect = TRect(intOffsetX, 0, bgWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          gDisplay.GetRenderBitmap()->DrawBitmapTransparent(ENull, aBitmap, rect, 0, aVerticalOffset);
        }
        else {
          gDisplay.GetRenderBitmap()->DrawBitmap(ENull, aBitmap, rect, 0, aVerticalOffset);
        }

      }
      else {
        drawWidth = 320 - priorDrawWidth;
        TRect rect = TRect(0, 0, drawWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          gDisplay.GetRenderBitmap()->DrawBitmapTransparent(ENull, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
        else {
          gDisplay.GetRenderBitmap()->DrawBitmap(ENull, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
      }
    }
    else { // Backgrounds that are too small for the canvas
      if (remainDrawWidth == canvasWidth) {
        drawWidth = bgWidth - intOffsetX;
        TRect rect = TRect(intOffsetX, 0, bgWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          gDisplay.GetRenderBitmap()->DrawBitmapTransparent(ENull, aBitmap, rect, 0, aVerticalOffset);
        }
        else {
          gDisplay.GetRenderBitmap()->DrawBitmap(ENull, aBitmap, rect, 0, aVerticalOffset);
        }
      }
      else {
        drawWidth = (remainDrawWidth > bgWidth) ? bgWidth : remainDrawWidth;
        TRect rect = TRect(0, 0, drawWidth - 1, aBitmap->Height() - 1);

        if (aDrawTransparent) {
          gDisplay.GetRenderBitmap()->DrawBitmapTransparent(ENull, aBitmap, rect,  priorDrawWidth, aVerticalOffset);
        }
        else {
          gDisplay.GetRenderBitmap()->DrawBitmap(ENull, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
      }
    }


    if (drawWidth == 0) {
//      printf("drawWidth == 0!\n");
      return;
    }

    priorDrawWidth += drawWidth;
    remainDrawWidth -= drawWidth;

    if (remainDrawWidth < 1) {
      return;
    }
  }
}