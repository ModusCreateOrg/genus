#include "Game.h"

static const TUint8 ARROW_TIMER = 3;
static const TUint8 BLOCK_TIMER = 15;
static const TUint8 ARROW_X = 4;
static const TUint8 BLOCK_X = 96;
static const TUint8 BLOCK_Y = 50;
static const TUint8 TEXT_Y = 100;

// special characters
static const char *STR_LEFT_ARROW  = "\xf";
static const char *STR_RIGHT_ARROW = "\xe";

class GRulesPlayfield : public BPlayfield {
public:
  GRulesPlayfield() {
    mFont = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);

    gResourceManager.LoadBitmap(HIGH_SCORES1_BMP, BKG_SLOT, IMAGE_ENTIRE);
    gResourceManager.LoadBitmap(COMMON_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);
    gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);

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
    gDisplay.renderBitmap->DrawStringShadow(ENull, aString, mFont, x, aY, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -4);
    return 18;
  }

  void Render() {
    gDisplay.renderBitmap->CopyPixels(mBackground);
    RenderString("HOW TO PLAY", 12);

    // Left arrow
    gDisplay.renderBitmap->DrawString(ENull, STR_LEFT_ARROW, mFont, ARROW_X, (SCREEN_HEIGHT - mFont->mHeight) / 2, mLeftArrowColor, -1);

    // Right arrow
    gDisplay.renderBitmap->DrawString(ENull, STR_RIGHT_ARROW, mFont, SCREEN_WIDTH - mFont->mWidth - ARROW_X, (SCREEN_HEIGHT - mFont->mHeight) / 2, mRightArrowColor, -1);
  }

  BFont *mFont;
  BBitmap *mBackground;
  TUint8 mLeftArrowColor = COLOR_TEXT;
  TUint8 mRightArrowColor = COLOR_TEXT;
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
    mNextTimer  = 3 * 30;
    mArrowTimer = 0;
  }

  ~RulesProcess() {
    delete mFont;
  }

protected:
  TInt RenderString(const char *aString, TInt aY) {
    TInt width = TInt(strlen(aString) * 12);
    TInt x     = (SCREEN_WIDTH - width) / 2;
    gDisplay.renderBitmap->DrawStringShadow(ENull, aString, mFont, x, aY, COLOR_TEXT, COLOR_TEXT_SHADOW, -1, -4);
    return 18;
  }

protected:
  TInt Text1() {
    mSprite->flags |= SFLAG_RENDER;
    TInt y = TEXT_Y;
    y += RenderString("Move the 2x2 blocks", y);
    y += RenderString("with the joystick.", y) + 16;
    y += RenderString("Drop blocks on board", y);
    y += RenderString("with the A button.", y);
    return y;
  }

  TInt Text2() {
    mSprite->flags |= SFLAG_RENDER;
    TInt y = TEXT_Y;
    y += RenderString("The B button rotates", y);
    y += RenderString("the blocks.", y);
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
    y += RenderString("Object is to get 2x2", y);
    y += RenderString("of the same color on", y);
    y += RenderString("the board.", y) + 16;
    y += RenderString("The matched blocks", y);
    y += RenderString("turn dark and the", y);
    y += RenderString("timer starts.", y);
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
    y += RenderString("Increase score by", y);
    y += RenderString("matching more while", y);
    y += RenderString("timer runs.", y);
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
    y += RenderString("When timer runs out,", y);
    y += RenderString("the dark blocks are", y);
    y += RenderString("removed from the board.", y) + 16;
    y += RenderString("The more blocks removed,", y);
    y += RenderString("the higher your score.", y);
    return y;
  }

  TInt Text6() {
    mSprite->flags &= ~SFLAG_RENDER;
    TInt y = TEXT_Y - 36;
    y += RenderString("Increase level by", y);
    y += RenderString("removing enough", y);
    y += RenderString("dark blocks.", y) + 16;
    y += RenderString("Game is over when", y);
    y += RenderString("the board has no", y);
    y += RenderString("space to drop another", y);
    y += RenderString("2x2.", y) + 16;
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
        Text3();
        break;
      case 3:
        Text4();
        break;
      case 4:
        Text5();
        break;
      case 5:
        Text6();
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
        mState = 5;
      }
      mArrowTimer = ARROW_TIMER;
      mRulesPlayfield->mLeftArrowColor = COLOR_TEXT_BG;
      gSoundPlayer.SfxMenuNavUp();
    }

    // Next screen
    if (gControls.WasPressed(JOYRIGHT | JOYDOWN)) {
      mState++;
      if (mState > 5) {
        mState = 0;
      }
      mArrowTimer = ARROW_TIMER;
      mRulesPlayfield->mRightArrowColor = COLOR_TEXT_BG;
      gSoundPlayer.SfxMenuNavDown();
    }

    // Exit
    if (gControls.WasPressed(BUTTON_ANY)) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }

    return ETrue;
  }

protected:
  TInt            mState;
  TInt            mNextTimer, mTimer, mArrowTimer;
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
