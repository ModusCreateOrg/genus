#include "GContinueContainer.h"
#include "GRestartWidget.h"
#include "GContinueWidget.h"
#include "GMainMenuProcess.h"

GContinueContainer::GContinueContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess) : GDialogWidget("Menu", aX, aY) {
  mProcess = aProcess;
  AddWidget((BWidget &) *new GRestartWidget());
  AddWidget((BWidget &) *new GContinueWidget());
}

GContinueContainer::~GContinueContainer() {}

TBool GContinueContainer::OnNavigate(TUint16 bits) {
  GDialogWidget::OnNavigate(bits);
  mProcess->ResetTimer();
  return ETrue;
}
