#include "TOptions.h"

TOptions::TOptions() {
  if (!Load()) {
    Reset();
  }
}

void TOptions::SetDefaults() {
  muted = EFalse;
  music = 0.5f;
  sfx = 0.875f;
  difficulty = 1;
}

void TOptions::Reset(TBool aSave) {
  SetDefaults();

  if (aSave) {
    Save();
  }
}

void TOptions::Save() {
  BStore f("Genus");
  f.Set("options", this, sizeof(TOptions));
}

TBool TOptions::Load() {
  BStore f("Genus");
  return f.Get("options", this, sizeof(TOptions));
}
