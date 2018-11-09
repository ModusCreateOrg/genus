//
// Created by Jesus Garcia on 11/5/18.
//

#include "GLevelGlacialMountains.h"
#include "Game.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif


GLevelGlacialMountains::GLevelGlacialMountains(GGameState *aGameEngine) {

  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS0_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS1_BMP, BKG2_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS2_BMP, BKG3_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS3_BMP, BKG4_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS4_BMP, BKG5_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS5_BMP, BKG6_SLOT, IMAGE_ENTIRE);

  mGameEngine = aGameEngine;
  mTextColor = 0;
  mRenderTarget = gDisplay.renderBitmap;

  bgOffset0 = 0;
  bgOffset1 = 0;
  bgOffset2 = 0;
  bgOffset3 = 0;
  bgOffset4 = 0;
  bgOffset5 = 0;

  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);
  mBackground1 = gResourceManager.GetBitmap(BKG2_SLOT);
  mBackground2 = gResourceManager.GetBitmap(BKG3_SLOT);
  mBackground3 = gResourceManager.GetBitmap(BKG4_SLOT);
  mBackground4 = gResourceManager.GetBitmap(BKG5_SLOT);
  mBackground5 = gResourceManager.GetBitmap(BKG6_SLOT);

  printf("mBackground0 dimensions: %i x %i\n", mBackground0->Width(), mBackground0->Height());
  printf("mBackground1 dimensions: %i x %i\n", mBackground1->Width(), mBackground1->Height());
  printf("mBackground2 dimensions: %i x %i\n", mBackground2->Width(), mBackground2->Height());
  printf("mBackground3 dimensions: %i x %i\n", mBackground3->Width(), mBackground3->Height());
  printf("mBackground4 dimensions: %i x %i\n", mBackground4->Width(), mBackground4->Height());
  printf("mBackground4 dimensions: %i x %i\n", mBackground5->Width(), mBackground5->Height());
}

GLevelGlacialMountains::~GLevelGlacialMountains()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG4_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG5_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG6_SLOT);
}




void GLevelGlacialMountains::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);


  // Base background
  bgOffset0 += .005;
  if ((int)bgOffset0 >= mBackground0->Width()) {
    bgOffset0= 0;
  }

  bgOffset1 += .008;
  if ((int)bgOffset1 >= mBackground1->Width()) {
    bgOffset1 = 0;
  }

//  bgOffset2 += .01;
//  if ((int)bgOffset2 >= mBackground2->Width()) {
//    bgOffset2 = 0;
//  }

  bgOffset3 += .01;
  if ((int)bgOffset3 >= mBackground3->Width()) {
    bgOffset3 = 0;
  }

  bgOffset4 += .3;
  if ((int)bgOffset4 >= mBackground4->Width()) {
    bgOffset4 = 0;
  }

  bgOffset5 += .5;
  if ((int)bgOffset5 >= mBackground5->Width()) {
    bgOffset5 = 0;
  }

}

void GLevelGlacialMountains::Render() {

//  memset(gDisplay.renderBitmap->mPixels, 0, 320*240); // debug purposes
  DrawScrolledBackground(mBackground0, bgOffset0, 0);
  DrawScrolledBackground(mBackground1, bgOffset1, 60, ETrue);
  DrawScrolledBackground(mBackground2, bgOffset2, 70, ETrue);
  DrawScrolledBackground(mBackground3, bgOffset3, 173, ETrue);
  DrawScrolledBackground(mBackground4, bgOffset4, 175, ETrue);
  DrawScrolledBackground(mBackground5, bgOffset5, gDisplay.renderBitmap->Height() - mBackground5->Height(), ETrue);

  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}

