#include "GScrollingLevel.h"





void GScrollingLevel::DrawScrolledBackground(BBitmap *aBitmap, TFloat aOffsetX, TUint aVerticalOffset, TBool aDrawTransparent) {

  TInt16 intOffsetX = (TInt16)aOffsetX,
      canvasWidth = gDisplay.renderBitmap->Width(),
      remainDrawWidth = canvasWidth, // Remaining width to draw, since we'll have to do multiple passes
  bgWidth = aBitmap->Width(),
      priorDrawWidth = 0;


  TInt16 imgWidthDelta = bgWidth - intOffsetX;

  // Background is too big for the canvas, so just draw the full canvas width and be done!
  if (imgWidthDelta >= canvasWidth) {
    TRect rect = TRect(intOffsetX, 0, bgWidth, aBitmap->Height());

    if (aDrawTransparent) {
      gDisplay.renderBitmap->DrawBitmapTransparent(ENull, aBitmap, rect, 0, aVerticalOffset);
    }
    else {
      gDisplay.renderBitmap->DrawBitmap(ENull, aBitmap, rect, 0, aVerticalOffset);
    }
    return;
  }


  while (remainDrawWidth > 0) {
    TInt16 drawWidth = 0;

    // Background is too big for the canvas
    if (bgWidth > canvasWidth) {
      if (remainDrawWidth == canvasWidth) {
        drawWidth = imgWidthDelta;
        TRect rect = TRect(intOffsetX, 0, bgWidth, aBitmap->Height());

        if (aDrawTransparent) {
          gDisplay.renderBitmap->DrawBitmapTransparent(ENull, aBitmap, rect, 0, aVerticalOffset);
        }
        else {
          gDisplay.renderBitmap->DrawBitmap(ENull, aBitmap, rect, 0, aVerticalOffset);
        }

      }
      else {
        drawWidth = SCREEN_WIDTH - priorDrawWidth;
        TRect rect = TRect(0, 0, drawWidth, aBitmap->Height());

        if (aDrawTransparent) {
          gDisplay.renderBitmap->DrawBitmapTransparent(ENull, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
        else {
          gDisplay.renderBitmap->DrawBitmap(ENull, aBitmap, rect, priorDrawWidth, aVerticalOffset);
        }
      }
    }
    else { // Backgrounds that are too small for the canvas
      if (remainDrawWidth == canvasWidth) {
        drawWidth = bgWidth - intOffsetX;
        TRect rect = TRect(intOffsetX, 0, bgWidth, aBitmap->Height());

        if (aDrawTransparent) {
          gDisplay.renderBitmap->DrawBitmapTransparent(ENull, aBitmap, rect, 0, aVerticalOffset);
        }
        else {
          gDisplay.renderBitmap->DrawBitmap(ENull, aBitmap, rect, 0, aVerticalOffset);
        }
      }
      else {
        drawWidth = (remainDrawWidth > bgWidth) ? bgWidth : remainDrawWidth;
        TRect rect = TRect(0, 0, drawWidth, aBitmap->Height());

        if (aDrawTransparent) {
          gDisplay.renderBitmap->DrawBitmapTransparent(ENull, aBitmap, rect,  priorDrawWidth, aVerticalOffset);
        }
        else {
          gDisplay.renderBitmap->DrawBitmap(ENull, aBitmap, rect, priorDrawWidth, aVerticalOffset);
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
