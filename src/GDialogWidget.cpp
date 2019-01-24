#include "GDialogWidget.h"

GDialogWidget::GDialogWidget(char *aTitle, TInt aX, TInt aY) : BDialogWidget(aTitle, aX, aY) {
}

GDialogWidget::GDialogWidget(const char *aTitle, TInt aX, TInt aY) : BDialogWidget(aTitle, aX, aY) {
}

GDialogWidget::~GDialogWidget() {

}

TBool GDialogWidget::OnNavigate(TUint16 bits) {
  if (bits & JOYUP) {
    gSoundPlayer.SfxMenuNavUp();
  } else if (bits & JOYDOWN) {
    gSoundPlayer.SfxMenuNavDown();
  }
  return ETrue;
}

