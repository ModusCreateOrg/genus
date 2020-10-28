#include "Game.h"
#include "GStage1Countryside.h"



GStage1Countryside::GStage1Countryside(GGameState *aGameEngine) {
  mGameEngine = aGameEngine;
  mRenderTarget = gDisplay.renderBitmap;
  mTextColor  = 0;

#ifdef STATIC_GAME_BACKGROUNDS
  gResourceManager.LoadBitmap(COUNTRYSIDE_STATIC_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);

#else
  gResourceManager.LoadBitmap(COUNTRYSIDE0_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(COUNTRYSIDE1_BMP, BKG2_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(COUNTRYSIDE2_BMP, BKG3_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(COUNTRYSIDE3_BMP, BKG4_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(COUNTRYSIDE4_BMP, BKG5_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(COUNTRYSIDE5_BMP, BKG6_SLOT, IMAGE_ENTIRE);

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

GStage1Countryside::~GStage1Countryside()  {
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



void GStage1Countryside::Animate() {
//  mTextColor += 1;
//  mTextColor %= 64;
//  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);


  // Base background
#ifndef STATIC_GAME_BACKGROUNDS
  bgOffset0 += .02;
  if ((int) bgOffset0 >= mBackground0->Width()) {
    bgOffset0 = 0;
  }

  bgOffset1 += .1;
  if ((int) bgOffset1 >= mBackground1->Width()) {
    bgOffset1 = 0;
  }

  bgOffset3 += .6;
  if ((int) bgOffset3 >= mBackground3->Width()) {
    bgOffset3 = 0;
  }

  bgOffset4 += 1;
  if ((int) bgOffset4 >= mBackground4->Width()) {
    bgOffset4 = 0;
  }

  bgOffset5 += .06;
  if ((int) bgOffset5 >= mBackground5->Width()) {
    bgOffset5 = 0;
  }
#endif
}

void GStage1Countryside::Render() {

#ifdef STATIC_GAME_BACKGROUNDS
  gDisplay.renderBitmap->CopyPixels(mBackground0);
#else
  DrawScrolledBackground(mBackground0, bgOffset0, 0);
  DrawScrolledBackground(mBackground1, bgOffset1, 95, ETrue);
  DrawScrolledBackground(mBackground3, bgOffset3, 189, ETrue);
  DrawScrolledBackground(mBackground4, bgOffset4, 212, ETrue);
  DrawScrolledBackground(mBackground5, bgOffset5, 10, ETrue);
#endif
  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}

