#include "TOptions.h"

TOptions::TOptions() {
  BStore f("Genus");
  if (!f.Get("options", this, sizeof(this))) {
    SetDefaults();
    Save();
  }
}

void TOptions::SetDefaults() {
  music = 50;
  difficulty = 1;
}

void TOptions::Save() {
  BStore f("Genus");
  f.Set("options", this, sizeof(this));
}
