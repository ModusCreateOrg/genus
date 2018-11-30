#include "Game.h"

//

class CreditsProcess : public BProcess {
public:
  CreditsProcess() {
    mFont  = new BFont(gResourceManager.GetBitmap(FONT_16x16_SLOT), FONT_16x16);
    mText  = TEXT_MODUS_LABS;
    mState = STATE_FADEIN;
    mColor = 0;
  }

  ~CreditsProcess() {
    delete mFont;
    mFont = ENull;
  }

protected:
  enum {
    TEXT_MODUS_LABS,
    TEXT_GAME_DESIGN,
    TEXT_VISUAL_DESIGN,
    TEXT_PROGRAMMING,
    TEXT_CI,
    TEXT_PM,
    TEXT_SOUND,
    TEXT_DIRECTOR,
  } mText;

  BFont *mFont;

  TInt RenderString(const char *aString, TInt aY) {
    TInt width = TInt(strlen(aString) * 12);
    TInt x     = (320 - width) / 2;
    gDisplay.renderBitmap->DrawString(ENull, aString, mFont, x, aY, COLOR_TEXT, -1, -4);
    return 18;
  }

  void RenderText() {
    TInt y = 144-24;
    switch (mText) {
      case TEXT_MODUS_LABS:
        BSprite::DrawSprite(ENull, CREDITS_MODUS_LABS_SLOT, 0, 48, y);
        break;
      case TEXT_GAME_DESIGN:
        y += RenderString("GAME DESIGN", y) + 8;
        y += RenderString("Jonathan Van Dalen", y);
        y += RenderString("Dmytro Kovalenko", y);
        break;
      case TEXT_VISUAL_DESIGN:
        y += RenderString("VISUAL DESIGN", y) + 8;
        y += RenderString("Dmytro Kovalenko", y);
        y += RenderString("Lorena Vargas", y);
        y += RenderString("Jonathan Van Dalen", y);
        y += RenderString("Drew Griffith", y);
        break;
      case TEXT_PROGRAMMING:
        y += RenderString("PROGRAMMING", y) + 8;
        y += RenderString("Mike Schwartz", y);
        y += RenderString("Michael Tintiuc", y);
        y += RenderString("Jay Garcia", y);
        y += RenderString("Don Anderson", y);
        break;
      case TEXT_CI:
        y += RenderString("CONTINUOUS INTEGRATION", y) + 8;
        y += RenderString("Don Anderson", y);
        y += RenderString("Richard Bullington-McGuire", y);
        y += RenderString("Haneez Haroon", y);
        y += RenderString("Housni Yakoob", y);
        break;
      case TEXT_PM:
        y += RenderString("PROJECT MANAGER", y) + 8;
        y += RenderString("Dave Collins", y);
        break;
      case TEXT_SOUND:
        y += RenderString("MUSIC AND SOUND EFFECTS", y) + 8;
        y += RenderString("Jay Garcia", y);
        break;
      case TEXT_DIRECTOR:
        y += RenderString("DIRECTOR", y) + 8;
        y += RenderString("Jay Garcia", y);
        break;
    }
  }

  enum {
    STATE_FADEIN,
    STATE_FADEOUT,
    STATE_WAIT,
  }     mState;

  TInt mTimer, mColor;

  TBool FadeInState() {
    mColor += (255 / 15);
    if (mColor > 255) {
      mColor = 255;
    }
    gDisplay.SetColor(COLOR_TEXT, mColor, mColor, mColor);
    if (mColor == 255) {
      mState = STATE_WAIT;
      mTimer = 2 * 30;
    }
    return ETrue;
  }

  TBool FadeOutState() {
    mColor -= (255 / 15);
    if (mColor < 0) {
      mColor = 0;
    }
    gDisplay.SetColor(COLOR_TEXT, mColor, mColor, mColor);
    if (mColor == 0) {
      mState = STATE_FADEIN;
      switch (mText) {
        case TEXT_MODUS_LABS:
          mText = TEXT_GAME_DESIGN;
          break;
        case TEXT_GAME_DESIGN:
          mText = TEXT_VISUAL_DESIGN;
          break;
        case TEXT_VISUAL_DESIGN:
          mText = TEXT_PROGRAMMING;
          break;
        case TEXT_PROGRAMMING:
          mText = TEXT_CI;
          break;
        case TEXT_CI:
          mText = TEXT_PM;
          break;
        case TEXT_PM:
          mText = TEXT_SOUND;
          break;
        case TEXT_SOUND:
          mText = TEXT_DIRECTOR;
          break;
        case TEXT_DIRECTOR:
          mText = TEXT_MODUS_LABS;
          break;
      }
    }
    return ETrue;
  }

  TBool WaitState() {
    mTimer--;
    if (mTimer < 0) {
      mState = STATE_FADEOUT;
    }
    return ETrue;
  }

  TBool RunBefore() {
    if (gControls.WasPressed(BUTTON_ANY)) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }

  TBool RunAfter() {
    RenderText();
    switch (mState) {
      case STATE_FADEIN:
        return FadeInState();
      case STATE_FADEOUT:
        return FadeOutState();
      case STATE_WAIT:
        return WaitState();
      default:
        Panic("TextProcess invalid state");
    }
    return ETrue;
  }
};

class GCreditsPlayfield : public BPlayfield {
public:
  GCreditsPlayfield() {
    gResourceManager.LoadBitmap(MODUS_LABS_SPRITE_BMP, CREDITS_MODUS_LABS_SLOT, IMAGE_ENTIRE);
    gResourceManager.LoadBitmap(TEAM_SPRITE_BMP, CREDITS_TEAM_SLOT, IMAGE_ENTIRE);
    mBackground = gResourceManager.GetBitmap(CREDITS_TEAM_SLOT);
    gDisplay.SetPalette(mBackground);
    gDisplay.SetColor(0, 0,0,0);
  }

  virtual ~GCreditsPlayfield() {
    gResourceManager.ReleaseBitmapSlot(CREDITS_MODUS_LABS_SLOT);
    gResourceManager.ReleaseBitmapSlot(CREDITS_TEAM_SLOT);
  }

public:
  void Render() {
    gDisplay.renderBitmap->Clear(0);
    BSprite::DrawSprite(ENull, CREDITS_TEAM_SLOT, 0, 48, 8);
  }

public:
  BBitmap *mBackground;
};

GCreditsState::GCreditsState() : BGameEngine(gViewPort) {
  mPlayfield = new GCreditsPlayfield();
  AddProcess(new CreditsProcess());
}

GCreditsState::~GCreditsState() {
//  delete mPlayfield;
}

