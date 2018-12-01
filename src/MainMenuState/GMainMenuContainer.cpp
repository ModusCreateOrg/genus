#include "GMainMenuContainer.h"
#include "GStartWidget.h"
#include "GOptionsWidget.h"
#include "GCreditsWidget.h"
#include "GMainMenuProcess.h"

GMainMenuContainer::GMainMenuContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess) : BDialogWidget("Menu", aX, aY) {
  mProcess = aProcess;
  AddWidget((BWidget &) *new GStartWidget());
  AddWidget((BWidget &) *new GOptionsWidget());
  AddWidget((BWidget &) *new GCreditsWidget());
}

GMainMenuContainer::~GMainMenuContainer() {

}

void GMainMenuContainer::Run() {
  TUint16 keys = gControls.dKeys;

  BDialogWidget::Run();

  if (keys & (JOYUP | JOYDOWN)) {
    mProcess->ResetTimer();
    gSoundPlayer.SfxMenuNav();
  }
}
