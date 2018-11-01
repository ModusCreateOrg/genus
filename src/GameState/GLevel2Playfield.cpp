// Created by jaygarcia on 10/23/18.
#include "Game.h"
#include "GLevel2Playfield.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#endif


GLevel2Playfield::GLevel2Playfield(GGameState *aGameEngine) {
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
  // TODO: Jay - always clean up what you make in the construtor
  // never delete things in slots, just release them
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG3_SLOT);
}




void GLevel2Playfield::Animate() {
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
    printf("Reset bgOffset2 %i\n", (int)bgOffset2);
    bgOffset2 = 0;
  }

}

void GLevel2Playfield::Render() {

  memset(gDisplay.renderBitmap->mPixels, 0, 320*240); // debug purposes
  DrawScrolledBackground(mBackground0, bgOffset0, 0);
  DrawScrolledBackground(mBackground1, bgOffset1, 30, ETrue); // @Mtintiuc -- Set to EFalse, and the overflow drawing goes away.
  DrawScrolledBackground(mBackground2, bgOffset2, gDisplay.renderBitmap->Height() - mBackground2->Height() + 1, ETrue); // Same with this code.


// #ifdef __XTENSA__
//   printf("DMA: %i    SPIRAM: %i\n",
//      heap_caps_get_free_size(MALLOC_CAP_8BIT | MALLOC_CAP_DMA),
//      heap_caps_get_free_size(MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM));

//   fflush(stdout);
// #endif
 mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}

