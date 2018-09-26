//
// Created by Michael Schwartz on 9/5/18.
//

#include "GPlayfield.h"
#include "GGameEngine.h"
#include <Display.h>
#include "Resources.h"
#include "GResources.h"

GPlayfield::GPlayfield(GGameEngine *aGameEngine) : BPlayfield(aGameEngine) {
  mGameEngine = aGameEngine;
  mDisplay = &display;
//  resourceManager.LoadBitmap(BKG7_BMP, BKG_SLOT, IMAGE_ENTIRE);
//  mBitmap = resourceManager.GetBitmap(BKG_SLOT);
//  display.SetPalette(mBitmap);
}

void GPlayfield::Render() {
  BViewPort *vp = mGameEngine->GetViewPort();
  mDisplay->renderBitmap->Dump();
  mDisplay->renderBitmap->Clear(2);
  mDisplay->renderBitmap->DrawSprite(vp, BKG_SLOT, 0, TInt(vp->mOffsetX) + 0, TInt(vp->mOffsetY + 0));
}
