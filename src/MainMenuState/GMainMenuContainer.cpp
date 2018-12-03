#include "GMainMenuContainer.h"
#include "GStartWidget.h"
#include "GOptionsWidget.h"
#include "GCreditsWidget.h"
#include "GMainMenuProcess.h"

GMainMenuContainer::GMainMenuContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess) : GDialogWidget("Menu", aX, aY) {
  mProcess = aProcess;
  AddWidget((BWidget &) *new GStartWidget());
  AddWidget((BWidget &) *new GOptionsWidget());
  AddWidget((BWidget &) *new GCreditsWidget());
}

GMainMenuContainer::~GMainMenuContainer() {}

TBool GMainMenuContainer::OnNavigate(TUint16 bits) {
  GDialogWidget::OnNavigate(bits);
  mProcess->ResetTimer();
  return ETrue;
}
