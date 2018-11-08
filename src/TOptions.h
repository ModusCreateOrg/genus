#ifndef GENUS_TOPTIONS_H
#define GENUS_TOPTIONS_H

#include "BTypes.h"
#include "BStore.h"

struct TOptions {
  TUint music;
  TUint difficulty;

  TOptions();
  void SetDefaults();
  void Save();
};

#endif
