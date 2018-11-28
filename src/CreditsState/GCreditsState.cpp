#include "Game.h"

// 48,32  team
// 48, 144  modus labs
// #6d6d6d background color

//

class TeamProcess : public BProcess {
public:
  TeamProcess(GCreditsState *aCreditsState) {
    mSprite = new BSprite(0, CREDITS_TEAM_SLOT, 0);
    mSprite->x            = 48;
    mSprite->y            = -96; // height
    mSprite->vy           = TFloat((96 - 32.0) / (1.0 * 30.0));     // 1 second
    mSprite->mImageNumber = 0;
    mSprite->flags |= SFLAG_MOVE | SFLAG_RENDER;
    aCreditsState->AddSprite(mSprite);
  }

  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (mSprite->y >= 32) {
      mSprite->flags &= ~SFLAG_MOVE;
      mSprite->y = 32;
    }
    return ETrue;
  }

protected:
  BSprite *mSprite;
};

class ModusLabsProcess : public BProcess {
public:
  ModusLabsProcess(GCreditsState *aCreditsState) {
    mSprite = new BSprite(0, CREDITS_MODUS_LABS_SLOT, 0);
    mSprite->x            = 48;
    mSprite->y            = 240 + 64; // height
    mSprite->vy           = TFloat((64 - 144) / (1.0 * 30.0));     // 1 second
    mSprite->mImageNumber = 0;
    mSprite->flags |= SFLAG_MOVE | SFLAG_RENDER;
    aCreditsState->AddSprite(mSprite);
    mState        = STATE_ENTER;
    mCreditsState = aCreditsState;
  }

  GCreditsState *mCreditsState;
  TInt          mTimer;

  enum {
    STATE_ENTER,
    STATE_WAIT,
    STATE_LEAVE
  }             mState;

  TBool StateEnter() {
    if (mSprite->y <= 144) {
      mSprite->flags &= ~SFLAG_MOVE;
      mSprite->y = 144;
      mState = STATE_WAIT;
      mTimer = 3 * 30;
    }
    return ETrue;
  }

  TBool StateWait() {
    if (--mTimer < 0) {
      mState = STATE_LEAVE;
      mSprite->vx = TFloat(320 - 48) / (1 * 30);
      mSprite->vy = 0;
      mSprite->flags |= SFLAG_MOVE;
    }
    return ETrue;
  }

  TBool StateLeave() {
    if (mSprite->x > 320) {
      mSprite->Remove();
      delete mSprite;
      mSprite = ENull;
      mCreditsState->StartText();
      return EFalse;
    }
    return ETrue;
  }

  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    switch (mState) {
      case STATE_ENTER:
        return StateEnter();
      case STATE_WAIT:
        return StateWait();
      case STATE_LEAVE:
        return StateLeave();
    }
    return ETrue;
  }

protected:
  BSprite *mSprite;
};

class CreditsProcess : public BProcess {
public:
  CreditsProcess() : BProcess() {
    printf("GCreditsProcess\n");
  }

public:
  TBool RunBefore() {
    return ETrue;
  }

  TBool RunAfter() {
    if (gControls.WasPressed(BUTTON_ANY)) {
      gGame->SetState(GAME_STATE_MAIN_MENU);
      return EFalse;
    }
    return ETrue;
  }
};

class TextProcess : public BProcess {
public:
  TextProcess() {
    mFont  = new BFont(gResourceManager.GetBitmap(FONT_8x8_SLOT), FONT_8x8);
    mText  = TEXT_GAME_DESIGN;
    mState = STATE_FADEIN;
    mColor = 109;
  }

  ~TextProcess() {
    delete mFont;
    mFont = ENull;
  }

protected:
  enum {
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
    TInt width = TInt(strlen(aString) * 8);
    TInt x     = (320 - width) / 2;
    gDisplay.renderBitmap->DrawString(ENull, aString, mFont, x, aY, COLOR_TEXT);
    return 9;
  }

  void RenderText() {
    TInt y = 144;
    switch (mText) {
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
    mColor += (255 / 30);
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
    mColor -= (255 / 30);
    if (mColor < 109) {
      mColor = 109;
    }
    gDisplay.SetColor(COLOR_TEXT, mColor, mColor, mColor);
    if (mColor == 109) {
      mState = STATE_FADEIN;
      switch (mText) {
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
          mText = TEXT_GAME_DESIGN;
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
    gDisplay.SetColor(0, 109, 109, 109);
  }

  virtual ~GCreditsPlayfield() {
    gResourceManager.ReleaseBitmapSlot(CREDITS_MODUS_LABS_SLOT);
    gResourceManager.ReleaseBitmapSlot(CREDITS_TEAM_SLOT);
  }

public:
  void Render() {
    gDisplay.renderBitmap->Clear(0);
  }

public:
  BBitmap *mBackground;
};

GCreditsState::GCreditsState() : BGameEngine(gViewPort) {
  mPlayfield = new GCreditsPlayfield();
  AddProcess(new CreditsProcess());
  AddProcess(new TeamProcess(this));
  AddProcess(new ModusLabsProcess(this));
}

GCreditsState::~GCreditsState() {
//  delete mPlayfield;
}

void GCreditsState::StartText() {
  AddProcess(new TextProcess());
}
