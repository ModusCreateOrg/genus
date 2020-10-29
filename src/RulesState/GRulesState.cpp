#include "Game.h"

static const TUint8 ARROW_TIMER      = 3;
static const TUint8 BLOCK_TIMER      = 15;
static const TUint8 BLOCK_TIMER_INIT = 7;
static const TUint8 ARROW_X          = 4;
static const TUint8 BLOCK_X          = 96;
static const TUint8 BLOCK_Y          = 50;
static const TUint8 TEXT_Y           = 107;



class GRulesPlayfield : public BPlayfield {
public:
  GRulesPlayfield() {
    mFont = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

    gResourceManager.LoadBitmap(HIGH_SCORES1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    gResourceManager.LoadBitmap(COMMON_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);
    gResourceManager.LoadBitmap(STAGE1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);

    mBackground = gResourceManager.GetBitmap(BKG_SLOT);
    BBitmap *playerBitmap = gResourceManager.GetBitmap(PLAYER_SLOT);

    gDisplay.SetPalette(mBackground, 0, 128);
    gDisplay.SetPalette(playerBitmap, 128, 128);
    gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
    gDisplay.SetColor(COLOR_TEXT_SHADOW, 0, 0, 0);
    gDisplay.SetColor(COLOR_TEXT_BG, 255, 92, 93);
  }

  ~GRulesPlayfield() {
    delete mFont;
    gResourceManager.ReleaseBitmapSlot(BKG_SLOT);
    gResourceManager.ReleaseBitmapSlot(COMMON_SLOT);
    gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  }

  TInt RenderString(const char *aString, TInt aY) {
    TInt width = TInt(strlen(aString) * 12);
    TInt x     = (SCREEN_WIDTH - width) / 2;
    gDisplay.renderBitmap->DrawStringShadow(
        ENull,
        aString,
        mFont,
        x,
        aY,
        (TInt16)COLOR_TEXT,
        COLOR_TEXT_SHADOW,
        (TInt16)COLOR_TEXT_TRANSPARENT,
        (TInt)-4);
    return 18;
  }

  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);

    // Page x of y
    char pagination[12];
    strcpy(&pagination[0], "Page ");
    pagination[5]  = '0' + mCurrentPage;
    strcpy(&pagination[6], " of ");
    pagination[10] = '0' + mTotalPages;
    pagination[11] = '\0';
    RenderString((const char*)pagination, 12);

    // Left arrow
    gDisplay.renderBitmap->DrawString(ENull, STR_LEFT_ARROW, mFont, ARROW_X, (SCREEN_HEIGHT - mFont->mHeight) / 2, mLeftArrowColor, COLOR_TEXT_TRANSPARENT);

    // Right arrow
    gDisplay.renderBitmap->DrawString(ENull, STR_RIGHT_ARROW, mFont, SCREEN_WIDTH - mFont->mWidth - ARROW_X, (SCREEN_HEIGHT - mFont->mHeight) / 2, mRightArrowColor, COLOR_TEXT_TRANSPARENT);
  }

  BFont *mFont;
  BBitmap *mBackground;
  TUint8 mLeftArrowColor = COLOR_TEXT;
  TUint8 mRightArrowColor = COLOR_TEXT;
  TUint mCurrentPage = 1;
  TUint mTotalPages = 5;
};

class RulesProcess : public BProcess {
public:
  RulesProcess(GRulesState *aRulesState, GRulesPlayfield *aRulesPlayfield) {
    mRulesState = aRulesState;
    mRulesPlayfield = aRulesPlayfield;

    mFont   = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
    mSprite = new GPlayerSprite();

    mSprite->x = BLOCK_X + 48;
    mSprite->y = BLOCK_Y;
    mSprite->flags |= SFLAG_RULES_BLOCK;

    mRulesState->AddSprite(mSprite);

    mState      = 0;
    mArrowTimer = 0;
    mTimer      = BLOCK_TIMER_INIT;
  }

  ~RulesProcess() {
    delete mFont;
  }

protected:
  void ResetSprite() {
    mSprite->mBlocks[0] = 16;
    mSprite->mBlocks[1] = 0;
    mSprite->mBlocks[2] = 16;
    mSprite->mBlocks[3] = 0;
  }

  TInt RenderString(const char *aString, TInt aY) {
    TInt width = TInt(strlen(aString) * 12);
    TInt x     = (SCREEN_WIDTH - width) / 2;
    gDisplay.renderBitmap->DrawStringShadow(ENull, aString, mFont, x, aY, COLOR_TEXT, COLOR_TEXT_SHADOW, COLOR_TEXT_TRANSPARENT, -4);
    return 18;
  }

protected:
  TInt Text1() {
    mSprite->flags |= SFLAG_RENDER;
    ResetSprite();

    TInt y = TEXT_Y;
    y += RenderString("Use the arrow keys", y);
    y += RenderString("to move the blocks", y);

    y += RenderString("as they enter at the", y);
    y += RenderString("top of the game board.", y);
    return y;
  }

  TInt Text2() {
    mSprite->flags |= SFLAG_RENDER;

    TInt y = TEXT_Y;
#ifdef __DINGUX__
    y += RenderString("Pressing the A button", y);
#else
    y += RenderString("Pressing the X key", y);
#endif
    y += RenderString("will rotate the blocks", y);
    y += RenderString("clockwise.", y) + 16;
    y += RenderString("Place the blocks on", y);
    y += RenderString("the board by pressing", y);
#ifdef __DINGUX__
    y += RenderString("the B button.", y);
#else
    y += RenderString("the Z key.", y);
#endif
    y += RenderString("to create color matches.", y);

    mTimer--;
    if (mTimer < 0) {
      mSprite->RotateRight();
      mTimer = BLOCK_TIMER;
    }
    return y;
  }

  TInt DrawBlock(TUint8 n, TInt x, TInt y, TInt row, TInt col) {
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, n, x + col * 16, y + row * 16);
    return 16;
  }

  TInt Text3() {
    mSprite->flags &= ~SFLAG_RENDER;
    TInt x = BLOCK_X;
    TInt y = BLOCK_Y;
    DrawBlock(0, x, y, 0, 0);
    DrawBlock(16, x, y, 0, 1);
    DrawBlock(21, x, y, 0, 2);
    DrawBlock(21, x, y, 0, 3);
    DrawBlock(0, x, y, 0, 4);
    DrawBlock(16, x, y, 0, 5);

    DrawBlock(0, x, y, 1, 0);
    DrawBlock(0, x, y, 1, 1);
    DrawBlock(21, x, y, 1, 2);
    DrawBlock(21, x, y, 1, 3);
    DrawBlock(0, x, y, 1, 4);
    DrawBlock(16, x, y, 1, 5);

    y = TEXT_Y;
    y += RenderString("Clear the board by", y);
    y += RenderString("grouping the same color", y);
    y += RenderString("in a 2x2 pattern.", y) + 16;
//    y += RenderString("clear to create ", y);

    y += RenderString("Grouped blocks will", y);
    y += RenderString("darken and start the", y);
    y += RenderString("bonus timer.", y);
    return y;
  }

  TInt Text4() {
    mSprite->flags &= ~SFLAG_RENDER;
    TInt x = BLOCK_X;
    TInt y = BLOCK_Y;
    DrawBlock(0, x, y, 0, 0);
    DrawBlock(16, x, y, 0, 1);
    DrawBlock(21, x, y, 0, 2);
    DrawBlock(21, x, y, 0, 3);
    DrawBlock(0, x, y, 0, 4);
    DrawBlock(21, x, y, 0, 5);
    DrawBlock(21, x, y, 0, 6);
    DrawBlock(21, x, y, 0, 7);

    DrawBlock(0, x, y, 1, 0);
    DrawBlock(0, x, y, 1, 1);
    DrawBlock(21, x, y, 1, 2);
    DrawBlock(21, x, y, 1, 3);
    DrawBlock(0, x, y, 1, 4);
    DrawBlock(21, x, y, 1, 5);
    DrawBlock(21, x, y, 1, 6);
    DrawBlock(21, x, y, 1, 7);

    y = TEXT_Y;
    y += RenderString("While the bonus timer", y);
    y += RenderString("is ticking, you can", y);
    y += RenderString("create more color", y);
    y += RenderString("combinations to increase", y);
    y += RenderString("your score!", y);
    return y;
  }

  TInt Text5() {
    mSprite->flags &= ~SFLAG_RENDER;
    TInt x = BLOCK_X;
    TInt y = BLOCK_Y;

    DrawBlock(0, x, y, 0, 0);
    DrawBlock(16, x, y, 0, 1);
    DrawBlock(0, x, y, 0, 4);
    DrawBlock(0, x, y, 1, 0);
    DrawBlock(0, x, y, 1, 1);
    DrawBlock(0, x, y, 1, 4);

    y = TEXT_Y;
    y += RenderString("Difficulty increases as", y);
    y += RenderString("you progress levels.", y) + 16;

    y += RenderString("Play until you run out", y);
    y += RenderString("of space to place", y);
    y += RenderString("incoming blocks.", y);
    return y;
  }

protected:
  TBool RunBefore() { return ETrue; }

  TBool RunAfter() {
    switch (mState) {
      case 0:
        Text1();
        break;
      case 1:
        Text2();
        break;
      case 2:
        // Reset sprite rotation and timer from previous page
        mTimer = BLOCK_TIMER_INIT;
        ResetSprite();
        Text3();
        break;
      case 3:
        Text4();
        break;
      case 4:
        Text5();
        break;
    }

    // Highlitght the arrows
    if (!mArrowTimer--) {
      mRulesPlayfield->mLeftArrowColor = COLOR_TEXT;
      mRulesPlayfield->mRightArrowColor = COLOR_TEXT;
    }

    // Previous screen
    if (gControls.WasPressed(JOYLEFT | JOYUP)) {
      mState--;
      if (mState < 0) {
        mState = 4;
      }
      mArrowTimer = ARROW_TIMER;
      mRulesPlayfield->mLeftArrowColor = COLOR_TEXT_BG;
      gSoundPlayer.SfxMenuNavUp();
    }

    // Next screen
    if (gControls.WasPressed(JOYRIGHT | JOYDOWN | BUTTON_SELECT)) {
      mState++;

      if (mState > 4) {
        mState = 0;

        gGame->SetState(GAME_STATE_MAIN_MENU);
        gSoundPlayer.SfxMenuCancel();
        return EFalse;
      }
//      mArrowTimer = ARROW_TIMER;
      mRulesPlayfield->mRightArrowColor = COLOR_TEXT_BG;
      gSoundPlayer.SfxMenuNavDown();
    }

    mRulesPlayfield->mCurrentPage = mState + 1;

    // Exit
    if (gControls.WasPressed(BUTTON_ANY)) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      gSoundPlayer.SfxMenuCancel();
      return EFalse;
    }

    return ETrue;
  }

protected:
  TInt            mState;
  TInt            mTimer, mArrowTimer;
  BFont           *mFont;
  GPlayerSprite   *mSprite;
  GRulesState     *mRulesState;
  GRulesPlayfield *mRulesPlayfield;
};

GRulesState::GRulesState() : BGameEngine(gViewPort) {
  mPlayfield = new GRulesPlayfield();
  AddProcess(new RulesProcess(this, (GRulesPlayfield*) mPlayfield));
}

GRulesState::~GRulesState() {}
