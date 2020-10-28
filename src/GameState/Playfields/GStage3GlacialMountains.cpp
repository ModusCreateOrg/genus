#include "GStage3GlacialMountains.h"
#include "Game.h"


GStage3GlacialMountains::GStage3GlacialMountains(GGameState *aGameEngine) {
  mGameEngine = aGameEngine;
  mTextColor = 0;
  mRenderTarget = gDisplay.renderBitmap;



#ifdef STATIC_GAME_BACKGROUNDS
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS_STATIC_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);

#else

  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS0_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS1_BMP, BKG2_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS2_BMP, BKG3_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS3_BMP, BKG4_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS4_BMP, BKG5_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(GLACIAL_MOUNTAINS5_BMP, BKG6_SLOT, IMAGE_ENTIRE);



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
#endif
}

GStage3GlacialMountains::~GStage3GlacialMountains()  {
#ifdef STATIC_GAME_BACKGROUNDS
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
#else
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG4_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG5_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG6_SLOT);
#endif
}




void GStage3GlacialMountains::Animate() {
//  mTextColor += 1;
//  mTextColor %= 64;
//  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);


#ifndef STATIC_GAME_BACKGROUNDS

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
#endif
}

void GStage3GlacialMountains::Render() {

//  memset(gDisplay.renderBitmap->mPixels, 0, 320*240); // debug purposes

#ifdef STATIC_GAME_BACKGROUNDS
  gDisplay.renderBitmap->CopyPixels(mBackground0);
#else
  DrawScrolledBackground(mBackground0, bgOffset0, 0);
  DrawScrolledBackground(mBackground1, bgOffset1, 60, ETrue);
  DrawScrolledBackground(mBackground2, bgOffset2, 70, ETrue);
  DrawScrolledBackground(mBackground3, bgOffset3, 173, ETrue);
  DrawScrolledBackground(mBackground4, bgOffset4, 175, ETrue);
  DrawScrolledBackground(mBackground5, bgOffset5, gDisplay.renderBitmap->Height() - mBackground5->Height(), ETrue);
#endif
  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}

