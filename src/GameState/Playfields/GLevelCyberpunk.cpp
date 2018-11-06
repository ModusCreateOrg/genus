// Created by jaygarcia on 10/23/18.
#include "Game.h"
#include "GLevelCyberpunk.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif


GLevelCyberpunk::GLevelCyberpunk(GGameState *aGameEngine) {

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

GLevelCyberpunk::~GLevelCyberpunk()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
}


void GLevelCyberpunk::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);

  bgOffset0 += 1;
  if ((int)bgOffset0 >= mBackground0->Width()) {
    bgOffset0= 0;
  }

  bgOffset1 += .2;
  if ((int)bgOffset1 >= mBackground1->Width()) {
    bgOffset1 = 0;
  }

  bgOffset2 += 1.3;
  if ((int)bgOffset2 >= mBackground2->Width()) {
    bgOffset2 = 0;
  }

}

void GLevelCyberpunk::Render() {

//  memset(gDisplay.renderBitmap->GetPixels(), 0, 320*240); // debug purposes
  DrawScrolledBackground(mBackground0, bgOffset0, 0);
  DrawScrolledBackground(mBackground1, bgOffset1, 30, ETrue);
  DrawScrolledBackground(mBackground2, bgOffset2, gDisplay.renderBitmap->Height() - mBackground2->Height() + 1, ETrue); // Same with this code.

 mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}

