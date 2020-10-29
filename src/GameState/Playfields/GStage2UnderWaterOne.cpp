#include "Game.h"
#include "GStage2UnderWaterOne.h"
#include "PrecalcSines.h"


GStage2UnderWaterOne::GStage2UnderWaterOne(GGameState *aGameEngine) {
  gResourceManager.LoadBitmap(UNDER_WATER_ONE_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mGameEngine = aGameEngine;
  mTextColor = 0;
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  mYSinIndex = 0;
  mXSinIndex = 0;

//  xOffset = (TInt8 *)AllocMem(320, MEMF_SLOW);
//  yComp   = (TInt8 *)AllocMem(240, MEMF_SLOW);
  mAnimSpeedX = .5;
  mAnimSpeedY = .25;
  mXTimer = mYTimer = 0;
  mXComp   = (TInt8 *)AllocMem(320, MEMF_FAST);
  mYOffset = (TInt8 *)AllocMem(240, MEMF_FAST);

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
  TInt16 workingXSinIndex = mXSinIndex;
  for (TInt16 x = 0; x < 320; x++) {
//    xOffset[x] = sin(mFrame * 0.15 + x * 0.06) * 4;
//    mXComp[x] = sin(mFrame * 0.11 + x * 0.12) * 3.0f;

    mXComp[x] = xSin[workingXSinIndex];
    workingXSinIndex++;
    if (workingXSinIndex > 319) {
      workingXSinIndex = 0;
    }
  }

  TInt16 workingYSinIndex = mYSinIndex;
  for (TInt16 y = 0; y < 240; y++) {
//    mYOffset[y] = sin(mFrame * 0.1 + y * 0.05) * 2.0f;
//    yComp[y] = sin(mFrame * 0.07 + y * 0.15) * 4;

    mYOffset[y] = ySin[workingYSinIndex];
    workingYSinIndex++;
    if (workingYSinIndex > 239) {
      workingYSinIndex = 0;
    }
  }

  mXTimer += mAnimSpeedX;
  mYTimer += mAnimSpeedY;

//  mXSinIndex++;
  mXSinIndex = (TInt16)mXTimer;
  if (mXSinIndex > 319) {
    mXTimer = mXSinIndex = 0;
  }

//  mYSinIndex++;
  mYSinIndex = (TInt16)mYTimer;
  if (mYSinIndex > 239) {
    mYTimer = mYSinIndex = 0;
  }

}

void GStage2UnderWaterOne::Render() {
  TUint8 *src = mBackground->GetPixels(),
         *dest = gDisplay.renderBitmap->GetPixels();

  int srcIndex = 8,
      destIndex = 0;

  for (TUint8 y = 0; y < 240; y++) {
    for (TInt16 x = 0; x < 320; x++) {
      dest[destIndex] = src[srcIndex + mYOffset[y] + mXComp[x]];

      srcIndex++;
      destIndex++;
    }

    srcIndex += 16;
  }

  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}
