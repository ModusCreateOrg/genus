#ifndef GENUS_GMAINMENUPLAYFIELD_H
#define GENUS_GMAINMENUPLAYFIELD_H

#include "Game.h"

class GMainMenuPlayfield : public BPlayfield {
public:
  GMainMenuPlayfield();
  virtual ~GMainMenuPlayfield();

public:
  TInt CenterText8(const char *s, TInt aY, TInt aColor = COLOR_TEXT, TInt aBackground = -1);
  TInt CenterText16(const char *s, TInt aY, TInt aColor = COLOR_TEXT, TInt aBackground = -1);
  void Render();

public:
  BFont   *mFont8, *mFont16;
  BBitmap *mBackground;
  BBitmap *mLogo;
  TInt    mState;
};

#endif //GENUS_GMAINMENUPLAYFIELD_H
