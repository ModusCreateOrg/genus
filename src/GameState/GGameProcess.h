#ifndef GENUS_GGAMEPROCESS_H
#define GENUS_GGAMEPROCESS_H

#include <BProcess.h>
#include "GGameBoard.h"
#include "GPlayerSprite.h"

class GGameState;

class GGameProcess : public BProcess {
public:
    GGameProcess(GGameState *aGameState);

    virtual ~GGameProcess();

    TInt BoardRow();

    TInt BoardCol();

public:
    TBool TimedControl(TUint16 aButton);

    TBool CanDrop();

    TBool Drop();

public:
    TBool StateGameOver();

    TBool StateControl();

    TBool StateRemoveBlocks();

public:
    void RemoveBlocks();

public:
    TBool RunBefore();

    TBool RunAfter();

public:
    TInt mState;
    TInt mRepeatTimer;
    TInt mBlinkTimer;
public:
    GPlayerSprite *mSprite;
    GGameState *mGameState;
    GGameBoard *mGameBoard;
public:
    TInt mRemoveRow, mRemoveCol;
    TInt mRemoveTimer;
    TUint32 mRemoveScore;
};

#endif //GENUS_GGAMEPROCESS_H
