#include "Game.h"

class GRulesPlayfield : public BPlayfield {
public:
  GRulesPlayfield() {
    mFont = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
  }

  ~GRulesPlayfield() {
    delete mFont;
  }

  TInt RenderString(const char *aString, TInt aY) {
    TInt width = TInt(strlen(aString) * 12);
    TInt x     = (320 - width) / 2;
    gDisplay.renderBitmap->DrawString(ENull, aString, mFont, x, aY, COLOR_TEXT, -1, -4);
    return 18;
  }

  void Render() {
    gDisplay.renderBitmap->Clear();
    RenderString("HOW TO PLAY", 4);
    gDisplay.renderBitmap->DrawString(ENull, "<", mFont, 0, 240-16, COLOR_TEXT, -1, -4);
    gDisplay.renderBitmap->DrawString(ENull, ">", mFont, 320-16, 240-16, COLOR_TEXT, -1, -4);

  }

  BFont *mFont;
};

class RulesProcess : public BProcess {
public:
  RulesProcess(GRulesState *aRulesState) {
    mFont   = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
    mSprite = new GPlayerSprite();
    mSprite->x = 160 - 16;
    mSprite->y = 48;
    aRulesState->AddSprite(mSprite);
    mState     = 0;
    mNextTimer = 3 * 30;
    mTimer     = 15;
  }

  ~RulesProcess() {
    delete mFont;
  }

protected:
  TInt RenderString(const char *aString, TInt aY) {
    TInt width = TInt(strlen(aString) * 12);
    TInt x     = (320 - width) / 2;
    gDisplay.renderBitmap->DrawString(ENull, aString, mFont, x, aY, COLOR_TEXT, -1, -4);
    return 18;
  }

protected:
  TInt Text1() {
    mSprite->flags |= SFLAG_RENDER;
    TInt y = 96;
    y += RenderString("Move the 2x2 blocks", y);
    y += RenderString("with the joystick.", y) + 32;
    y += RenderString("Drop blocks on board", y);
    y += RenderString("with the A button.", y);
    return y;
  }

  TInt Text2() {
    mSprite->flags |= SFLAG_RENDER;
    TInt y = 96;
    y += RenderString("The B button rotates", y);
    y += RenderString("the blocks.", y);
    mTimer--;
    if (mTimer < 0) {
      mSprite->RotateRight();
      mTimer = 15;
    }
    return y;
  }

  TInt DrawBlock(TUint8 n, TInt x, TInt y, TInt row, TInt col) {
    BSprite::DrawSprite(gViewPort, PLAYER_SLOT, n, x + col * 16, y + row * 16);
    return 16;
  }

  TInt Text3() {
    mSprite->flags &= ~SFLAG_RENDER;
    TInt x = 160-48;
    TInt y = 40;
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

    y = 88;
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
    TInt x = 160-48-16;
    TInt y = 40;
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


    y = 88;
    y += RenderString("Increase score by", y);
    y += RenderString("matching more while", y);
    y += RenderString("timer runs.", y);
    return y;
  }

  TInt Text5() {
    mSprite->flags &= ~SFLAG_RENDER;
    TInt x = 160-48-16;
    TInt y = 40;
    DrawBlock(0, x, y, 0, 0);
    DrawBlock(16, x, y, 0, 1);
//    DrawBlock(21, x, y, 0, 2);
//    DrawBlock(21, x, y, 0, 3);
    DrawBlock(0, x, y, 0, 4);
//    DrawBlock(21, x, y, 0, 5);
//    DrawBlock(21, x, y, 0, 6);
//    DrawBlock(21, x, y, 0, 7);

    DrawBlock(0, x, y, 1, 0);
    DrawBlock(0, x, y, 1, 1);
//    DrawBlock(21, x, y, 1, 2);
//    DrawBlock(21, x, y, 1, 3);
    DrawBlock(0, x, y, 1, 4);
//    DrawBlock(21, x, y, 1, 5);
//    DrawBlock(21, x, y, 1, 6);
//    DrawBlock(21, x, y, 1, 7);


    y = 88;
    y += RenderString("When timer runs out,", y);
    y += RenderString("the dark blocks are", y);
    y += RenderString("removed from the board.", y)+16;
    y += RenderString("The more blocks removed,", y);
    y += RenderString("the higher your score.", y);
    return y;
  }

  TInt Text6() {
    mSprite->flags &= ~SFLAG_RENDER;
    TInt x = 160-48-16;
    TInt y = 40;
    y += RenderString("Increase level by", y);
    y += RenderString("removing enough", y);
    y += RenderString("dark blocks.", y) + 16;
    y += RenderString("Game is over when", y);
    y += RenderString("the board has no", y);
    y += RenderString("space to drop another", y);
    y += RenderString("2x2.", y)+16;
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
    if (gControls.WasPressed(JOYLEFT)) {
      mState--;
      if (mState < 0) {
        mState = 5;
      }
    }
    if (gControls.WasPressed(JOYRIGHT)) {
      mState++;
      if (mState > 5) {
        mState = 0;
      }
    }
    // TODO: michael - navigate to main screen
    return ETrue;
  }

protected:
  TInt          mState;
  TInt          mNextTimer, mTimer;
  BFont         *mFont;
  GPlayerSprite *mSprite;
};

GRulesState::GRulesState() : BGameEngine(gViewPort) {
  gResourceManager.ReleaseBitmapSlot(PLAYER_SLOT);
  gResourceManager.LoadBitmap(LEVEL1_SPRITES_BMP, PLAYER_SLOT, IMAGE_16x16);
  gResourceManager.LoadBitmap(COMMON_SPRITES_BMP, COMMON_SLOT, IMAGE_16x16);
  BBitmap *playerBitmap = gResourceManager.GetBitmap(PLAYER_SLOT);
  // TODO: Jay - this logic can be moved to BPlayfield children
  // this assumes BKG_SLOT bmp has the correct palette for the display
  gDisplay.SetPalette(playerBitmap, 128, 128);
  gDisplay.SetColor(COLOR_TEXT, 255, 255, 255);
  gDisplay.SetColor(COLOR_TEXT_SHADOW, 0, 0, 0);
  mPlayfield = new GRulesPlayfield();
  AddProcess(new RulesProcess(this));
}

GRulesState::~GRulesState() {

}

