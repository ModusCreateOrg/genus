#include "GResetWidget.h"
#include "Game.h"

GResetWidget::GResetWidget() : BButtonWidget("RESET GAME", COLOR_TEXT, COLOR_TEXT_BG) {
  mHeight = 24;
}

GResetWidget::~GResetWidget() {

}

TInt GResetWidget::Render(TInt aX, TInt aY) {
  TInt h = 0;
  TInt dy = BButtonWidget::Render(aX, aY);
  h += dy;
  return h;
}

void GResetWidget::Select() {
  printf("TODO: Reset Game\n");
}
