//
// Created by Jesus Garcia on 11/5/18.
//

#ifndef GENUS_GLEVELSPACE_H
#define GENUS_GLEVELSPACE_H

#include "GGameState.h"
#include "GScrollingLevel.h"

#if 1
const int NUM_STARS = 120;

class GStage6Space : public GScrollingLevel {
public:
  GStage6Space(GGameState *aGameEngine);

  ~GStage6Space();

protected:
  void InitStar(TInt aIndex) {
    mStarX[aIndex] = 256 - Random(0, 512);
    mStarY[aIndex] = 256 - Random(0, 512);
    mStarZ[aIndex] = mCameraZ + Random(200, 512);
  }

protected:
  void Animate();
  void Render();
protected:
  TInt       mStarX[NUM_STARS],
             mStarY[NUM_STARS];
  TFloat     mStarZ[NUM_STARS],
             mCameraZ, mOldCameraZ;
protected:
  GGameState *mGameEngine;
  BBitmap *mBackground0, *mBackground1;
};

#else
class Star {
public:
  float mX, mY, mZ;
  int mScreenX, mScreenY, mOldScreenX, mOldScreenY, mSpeed;

  void Randomize(int aMinX, int aMaxX, int aMinY, int aMaxY, int aMinZ, int aMaxZ, int aMinSpeed, int aMaxSpeed) {
    mX = Random() % (aMaxX - aMinX + 1) + aMinX;
    mY = Random() % (aMaxY - aMinY + 1) + aMinY;
    mZ = Random() % (aMaxZ - aMinZ + 1) + aMinZ;
    mSpeed = Random() % (aMaxSpeed - aMinSpeed + 1) + aMinSpeed;
  };
};

class GStage6Space : public GScrollingLevel {
public:
  GStage6Space(GGameState *aGameEngine);
  ~GStage6Space();

protected:
  Star *mStars;
  int mCurrSpeed;
  bool mBoostSpeed;
  long mActualTime = 0;
  long mSpeedMillis = 0;
  int mStarCount = 40;

public:
  void Animate();
  void Render();

  GGameState *mGameEngine;
  TUint8 mTextColor;
  BBitmap *mBackground0;
  BBitmap *mBackground1;
};
#endif


#endif //GENUS_GLEVELSPACE_H
