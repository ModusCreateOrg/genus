#include "GContinueGameContainer.h"
#include "GNewGameWidget.h"
#include "GContinueWidget.h"
#include "GCancelWidget.h"
#include "GMainMenuProcess.h"

GContinueGameContainer::GContinueGameContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess) : GDialogWidget("Menu", aX, aY) {
  mProcess = aProcess;
  AddWidget((BWidget &) *new GContinueWidget());
  AddWidget((BWidget &) *new GNewGameWidget());
  AddWidget((BWidget &) *new GCancelWidget(mProcess));
}

GContinueGameContainer::~GContinueGameContainer() {}

TBool GContinueGameContainer::OnNavigate(TUint16 bits) {
  GDialogWidget::OnNavigate(bits);
  mProcess->ResetTimer();
  return ETrue;
}
