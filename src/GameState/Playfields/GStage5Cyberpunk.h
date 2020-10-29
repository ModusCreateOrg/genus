#ifndef GENUS_GLEVEL2PLAYFIELD_H
#define GENUS_GLEVEL2PLAYFIELD_H

#include "GameState/GGameState.h"
#include "GScrollingLevel.h"

class BuildingLights;
class TowersLights;
class ModusNeonLamp;
class BottleNeonLamp;
class ModusEasterEgg;

class GStage5Cyberpunk : public GScrollingLevel {
public:
  GStage5Cyberpunk(GGameState *aGameEngine);
  ~GStage5Cyberpunk();

  void Animate();
  void Render();


public:
  GGameState *mGameEngine;
  BBitmap *mBackground0;

#ifndef STATIC_GAME_BACKGROUNDS
  BBitmap *mBackground1;
  BBitmap *mBackground2;

  TFloat bgOffset0;
  TFloat bgOffset1;
  TFloat bgOffset2;
#endif

  TUint8 mTextColor;

  // Process list
  BuildingLights *mBuildingLightsProcess;
  TowersLights   *mTowerLightsProcess;
  ModusNeonLamp  *mModusNeonLampProcess;
  BottleNeonLamp *mBottleNeonLampProcess;
  ModusEasterEgg *mModusEasterEggProcess;
};


#endif //GENUS_GLEVEL2PLAYFIELD_H

