#ifndef GSOUNDPLAYER_H
#define GSOUNDPLAYER_H

#include "BSoundEngine.h"

#include "Resources.h"


class GSoundPlayer : public BBase {
private:
    TUint8 mNumberFxChannels;
    TUint8 mNumberFxSlots;

    TUint8 mMaxSongs;
    TUint8 mMaxEffects;
    SongSlot *mSongSlots; // Used to store number of slots

public:
    ~GSoundPlayer();
    void Init(TUint8 aNumberFxChannels);

    BRaw *FindRawSongFileById(TInt16 aResourceId);
    TBool LoadEffects();
    TBool PlayMusic(TInt16 aResourceId);
    void MuteMusic(TBool aMuted);

    void TriggerSfx(TUint16 aSfxNumber, TInt8 aChannel = -1);
    TBool SetMusicVolume(TFloat aPercent) {
      return soundEngine.SetMusicVolume(aPercent);
    }
    TBool SetEffectsVolume(TFloat aPercent) {
      return soundEngine.SetEffectsVolume(aPercent);
    }
    // SFX Methods //

  // SFX Methods //
  void SfxGoodDrop();
  void SfxRotateRight();
  void SfxRotateLeft();
  void SfxBadDrop();
  void SfxCombo();
  void SfxMoveBlock();
  void SfxExplodeBlock();
  void SfxOptionSelect();
  void SfxMenuNavUp();
  void SfxMenuNavDown();
  void SfxMenuAccept();
  void SfxMenuCancel();
  void SfxNextLevel();
  void SfxNextStage();
  void SfxSaveGame();
};


extern GSoundPlayer gSoundPlayer;

#endif //GSOUNDPLAYER_H
