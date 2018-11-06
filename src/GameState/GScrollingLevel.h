//
// Created by Jesus Garcia on 10/28/18.
//

#ifndef GENUS_GSCROLLINGLEVEL_H
#define GENUS_GSCROLLINGLEVEL_H



#include "GGameState.h"

class GScrollingLevel : public BPlayfield {
public:


public:

protected:
  BBitmap *mRenderTarget;
  TBool mUseCustomRenderTarget;

  void DrawScrolledBackground(BBitmap *aBitmap, TFloat aOffsetX, TUint aVerticalOffset, TBool aDrawTransparent = EFalse);

};



#endif //GENUS_GSCROLLINGLEVEL_H
