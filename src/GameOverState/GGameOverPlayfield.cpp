#include "GGameOverPlayfield.h"

GGameOverPlayfield::GGameOverPlayfield() {
  gResourceManager.LoadBitmap(MENU_BACKGROUND_BMP, BKG_SLOT, IMAGE_ENTIRE);
  mBackground = gResourceManager.GetBitmap(BKG_SLOT);
  gDisplay.SetPalette(mBackground);
  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_BG, 0,0,0);
}

GGameOverPlayfield::~GGameOverPlayfield() {
  gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
}

void GGameOverPlayfield::Render() {
  gDisplay.renderBitmap->CopyPixels(mBackground);
}

