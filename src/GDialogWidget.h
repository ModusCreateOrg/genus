#ifndef GENUS_GDIALOGWIDGET_H
#define GENUS_GDIALOGWIDGET_H

#include "Game.h"

class GDialogWidget : public BDialogWidget {
public:
  GDialogWidget(char *aTitle, TInt aX, TInt aY);
  GDialogWidget(const char *aTitle, TInt aX, TInt aY);
  virtual ~GDialogWidget();
  TBool OnNavigate(TUint16 bits);
};

#endif //GENUS_GDIALOGWIDGET_H
