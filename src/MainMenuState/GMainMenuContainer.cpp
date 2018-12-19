#include "GMainMenuContainer.h"
#include "GContinueWidget.h"
#include "GStartWidget.h"
#include "GOptionsWidget.h"
#include "GRulesWidget.h"
#include "GCreditsWidget.h"
#include "GMainMenuProcess.h"

GMainMenuContainer::GMainMenuContainer(TInt aX, TInt aY, GMainMenuProcess *aProcess) : GDialogWidget("Menu", aX, aY) {
  mProcess = aProcess;
  if (gOptions->gameProgress.savedState) {
    AddWidget((BWidget &) *new GContinueWidget());
  }
  AddWidget((BWidget &) *new GStartWidget());
  AddWidget((BWidget &) *new GOptionsWidget());
  AddWidget((BWidget &) *new GRulesWidget());
  AddWidget((BWidget &) *new GCreditsWidget());
}

GMainMenuContainer::~GMainMenuContainer() {}

TBool GMainMenuContainer::OnNavigate(TUint16 bits) {
  GDialogWidget::OnNavigate(bits);
  mProcess->ResetTimer();
  return ETrue;
}
