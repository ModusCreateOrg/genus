//
// Created by Jesus Garcia on 10/23/18.
//

#ifndef GENUS_GLEVEL2PLAYFIELD_H
#define GENUS_GLEVEL2PLAYFIELD_H

#include "GameState/GGameState.h"
#include "GScrollingLevel.h"

class BuildingLights;
class TowersLights;
class ModusNeonLamp;
class BottleNeonLamp;
class ModusEasterEgg;

class GLevelCyberpunk : public GScrollingLevel {
public:
  GLevelCyberpunk(GGameState *aGameEngine);
  ~GLevelCyberpunk();

  void Animate();
  void Render();


public:
  GGameState *mGameEngine;
  BBitmap *mBackground0;

#ifndef STATIC_GAME_BACKGROUNDS
  BBitmap *mBackground1;
  BBitmap *mBackground2;

  float bgOffset0;
  float bgOffset1;
  float bgOffset2;
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

