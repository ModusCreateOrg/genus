#ifndef GENUS_TOPTIONS_H
#define GENUS_TOPTIONS_H

#include "BTypes.h"
#include "BStore.h"

struct TOptions {
  TBool muted;
  TUint difficulty;
  TFloat music;
  TFloat sfx;

  TOptions();
  void SetDefaults();
  void Save();
  TBool Load();
};

#endif
