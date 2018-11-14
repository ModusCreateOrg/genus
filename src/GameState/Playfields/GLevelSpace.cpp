//
// Created by Jesus Garcia on 11/5/18.
//

#include "GLevelSpace.h"
#include "Game.h"

#ifdef __XTENSA__
#include <math.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_task_wdt.h"
#endif



#define STAR_SPEED_MIN 10 // Minimum movement in pixels per update. (value is inclusive)
#define STAR_SPEED_MAX 30 // Maximum movement in pixels per update. (value is inclusive)

#define RANDOM_Z_MIN 900
#define RANDOM_Z_MAX 1900


GLevelSpace::GLevelSpace(GGameState *aGameEngine) {
  mGameEngine = aGameEngine;
  mTextColor = 0;
  mRenderTarget = gDisplay.renderBitmap;

  mCurrSpeed = 10;
  mBoostSpeed = false;

  mStars = (Star *)AllocMem(mStarCount * sizeof(Star), MEMF_SLOW);

  for (int i = 0; i < mStarCount; i++) {
    mStars[i].Randomize(
      -500,
      1000,
      -500,
      1000,
      0,
      1,
      STAR_SPEED_MIN,
      STAR_SPEED_MAX
    );
  }


  gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(SPACE_STATIC_TOP_LEFT_BMP, BKG_SLOT, IMAGE_ENTIRE);
  gResourceManager.LoadBitmap(SPACE_STATIC_BOTTOM_RIGHT_BMP, BKG2_SLOT, IMAGE_ENTIRE);

  mBackground0 = gResourceManager.GetBitmap(BKG_SLOT);
  mBackground1 = gResourceManager.GetBitmap(BKG2_SLOT);

}

GLevelSpace::~GLevelSpace()  {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
  gResourceManager.ReleaseBitmapSlot(BKG2_SLOT);
}




void GLevelSpace::Animate() {
  mTextColor += 1;
  mTextColor %= 64;
  gDisplay.renderBitmap->SetColor(COLOR_TEXT, 0, 192 + mTextColor, 192 + mTextColor);
}

void GLevelSpace::Render() {


#ifdef STATIC_GAME_BACKGROUNDS

  memset(gDisplay.renderBitmap->GetPixels(), 86, 320*240);
  TRect rect = TRect(0, 0, mBackground0->Width() - 1, mBackground0->Height() - 1);
  gDisplay.renderBitmap->DrawBitmapTransparent(ENull, mBackground0, rect, 0, 0);
#else
//  DrawScrolledBackground(mBackground0, bgOffset0, 0);
//  DrawScrolledBackground(mBackground1, bgOffset1, 60, ETrue);
//  DrawScrolledBackground(mBackground2, bgOffset2, 70, ETrue);
//  DrawScrolledBackground(mBackground3, bgOffset3, 173, ETrue);
//  DrawScrolledBackground(mBackground4, bgOffset4, 175, ETrue);
//  DrawScrolledBackground(mBackground5, bgOffset5, gDisplay.renderBitmap->Height() - mBackground5->Height(), ETrue);
#endif


//  float travelX = 0,
//        travelY = 0,
//        travelZ = 0;

  // Loop through each star.
  for (int i = 0; i < mStarCount; i++) {

    mStars[i].mZ -= mCurrSpeed;
//
    // Leaving this here in case we want to use joystick-based changes
//    if (travelY != 0) {
//      float temp_y = mStars[i].mY;
//      float temp_z = mStars[i].mZ;
//      mStars[i].mY = temp_y * cos(travelY) - temp_z * sin(travelY);
//      mStars[i].mZ = temp_z * cos(travelY) + temp_y * sin(travelY);
//    }
//
//    if (travelX != 0) {
//      float temp_x = mStars[i].mX;
//      float temp_y = mStars[i].mY;
//      mStars[i].mX = temp_x * cos(travelX) - temp_y * sin(travelX);
//      mStars[i].mY = temp_y * cos(travelX) + temp_x * sin(travelX);
//    }
//
//    if (travelZ != 0) {
//      float temp_x = mStars[i].mX;
//      float temp_z = mStars[i].mZ;
//      mStars[i].mX = temp_x * cos(travelZ) - temp_z * sin(travelZ);
//      mStars[i].mZ = temp_z * cos(travelZ) + temp_x * sin(travelZ);
//    }

    mStars[i].mScreenX = mStars[i].mX / mStars[i].mZ * 100 + 320 / 2;
    mStars[i].mScreenY = mStars[i].mY / mStars[i].mZ * 100 + 240 / 2;

#ifdef __XTESNA__
    mActualTime = xTaskGetTickCount();
#else
    mActualTime = Milliseconds();
#endif

    if (mBoostSpeed && mCurrSpeed <= STAR_SPEED_MAX && mActualTime - mSpeedMillis >= 25) {
      mCurrSpeed = mCurrSpeed + 5;
      mSpeedMillis = mActualTime;
    }

    if (!mBoostSpeed && mCurrSpeed > STAR_SPEED_MIN && mActualTime - mSpeedMillis >= 10) {
      mCurrSpeed -= 5;
      mSpeedMillis = mActualTime;
    }
    if (mCurrSpeed < STAR_SPEED_MIN) {
      mCurrSpeed = STAR_SPEED_MIN;
    }

    //If the mStars go off the screen remove them and re-draw. If the mStars hang out in the center remove them also
    if (mStars[i].mScreenX > 320 || mStars[i].mScreenX < 0 || mStars[i].mScreenY > 240 || mStars[i].mScreenY < 0 || (mStars[i].mScreenX == 320 >> 1 && mStars[i].mScreenY == 240 >> 1) ) {

      mStars[i].Randomize(
        -1000,
        1000,
        -500,
        500,
        RANDOM_Z_MIN,
        RANDOM_Z_MAX,
        STAR_SPEED_MIN,
        STAR_SPEED_MAX
      );

      mStars[i].mScreenX = mStars[i].mX / mStars[i].mZ * 100 + 320 / 2;
      mStars[i].mScreenY = mStars[i].mY / mStars[i].mZ * 100 + 240 / 2;
      mStars[i].mOldScreenX = mStars[i].mScreenX;
      mStars[i].mOldScreenY = mStars[i].mScreenY;
    }


    // Draw the star at its new coordinate.
    gDisplay.renderBitmap->DrawLine(
      ENull,
      mStars[i].mScreenX,
      mStars[i].mScreenY,
      mStars[i].mOldScreenX,
      mStars[i].mOldScreenY,
      100 //colors[i]
    );

    //keep track of the old spot
    mStars[i].mOldScreenX = mStars[i].mScreenX;
    mStars[i].mOldScreenY = mStars[i].mScreenY;
  }




  rect = TRect(0, 0, mBackground1->Width() - 1, mBackground1->Height() - 1);
  gDisplay.renderBitmap->DrawBitmapTransparent(
    ENull,
    mBackground1,
    rect,
    gDisplay.renderBitmap->Width() - mBackground1->Width(),
    gDisplay.renderBitmap->Height() - mBackground1->Height()
  );


  mGameEngine->mGameBoard.Render(BOARD_X, BOARD_Y);
}


