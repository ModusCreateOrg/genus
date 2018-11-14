//
// Created by Jesus Garcia on 11/5/18.
//

#ifndef GENUS_GLEVELSPACE_H
#define GENUS_GLEVELSPACE_H

#include "GGameState.h"
#include "GScrollingLevel.h"




class Star {
public:
  float mX, mY, mZ;
  int mScreenX, mScreenY, mOldScreenX, mOldScreenY, mSpeed;

  void Randomize(int aMinX, int aMaxX, int aMinY, int aMaxY, int aMinZ, int aMaxZ, int aMinSpeed, int aMaxSpeed) {
    mX = rand() % (aMaxX - aMinX + 1) + aMinX;
    mY = rand() % (aMaxY - aMinY + 1) + aMinY;
    mZ = rand() % (aMaxZ - aMinZ + 1) + aMinZ;
    mSpeed = rand() % (aMaxSpeed - aMinSpeed + 1) + aMinSpeed;
  };
};

class GLevelSpace : public GScrollingLevel {
public:
  GLevelSpace(GGameState *aGameEngine);
  ~GLevelSpace();

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

#ifndef STATIC_GAME_BACKGROUNDS

  BBitmap *mBackground2;
  BBitmap *mBackground3;
  BBitmap *mBackground4;
  BBitmap *mBackground5;

  float bgOffset0;
  float bgOffset1;
  float bgOffset2;
  float bgOffset3;
  float bgOffset4;
  float bgOffset5;
#endif
};




#endif //GENUS_GLEVELGLACIALMOUNTAINS_H
