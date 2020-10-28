#include "Game.h"
#include "GStage2UnderWaterOne.h"
#include "PrecalcSines.h"

//int8_t *xOffset;
//
//int8_t *yComp;


GStage2UnderWaterOne::GStage2UnderWaterOne(GGameState *aGameEngine) {
  gResourceManager.LoadBitmap(UNDER_WATER_ONE_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mGameEngine = aGameEngine;
  mTextColor = 0;
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  mYSinIndex = 0;
  mXSinIndex = 0;

//  xOffset = (int8_t *)AllocMem(320, MEMF_SLOW);
  mXComp   = (int8_t *)AllocMem(320, MEMF_SLOW);
  mYOffset = (int8_t *)AllocMem(240, MEMF_SLOW);
//  yComp   = (int8_t *)AllocMem(240, MEMF_SLOW);

}

GStage2UnderWaterOne::~GStage2UnderWaterOne()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);

  FreeMem(mYOffset);
  FreeMem(mXComp);
}



void GStage2UnderWaterOne::Animate() {
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

void GStage2UnderWaterOne::Render() {
  TUint8 *src = mBackground->GetPixels(),
          *dest = gDisplay.renderBitmap->GetPixels();

  int srcIndex = 8,
      destIndex = 0;

  for (TUint8 y = 0; y < 240; y++) {
    for (int x = 0; x < 320; x++) {
      dest[destIndex] = src[srcIndex + mYOffset[y] + mXComp[x]];

      srcIndex++;
      destIndex++;
    }

    srcIndex += 16;
  }

  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}
