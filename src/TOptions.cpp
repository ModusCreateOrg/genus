#include "TOptions.h"

TOptions::TOptions() {
  if (!Load()) {
    SetDefaults();
    Save();
  }
}

void TOptions::SetDefaults() {
  muted = EFalse;
  music = 0.5f;
  sfx = 0.96f;
  difficulty = 1;
}

void TOptions::Save() {
  BStore f("Genus");
  f.Set("options", this, sizeof(TOptions));
}

TBool TOptions::Load() {
  BStore f("Genus");
  return f.Get("options", this, sizeof(TOptions));
}
