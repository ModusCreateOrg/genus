//
// Created by Jesus Garcia on 10/2/18.
//
#ifndef GSOUNDPLAYER_H
#define GSOUNDPLAYER_H
#include <Audio.h>
#include <BTypes.h>
#include <BBase.h>
#include <BResourceManager.h>


/**
 * Abstract sound player class.
 *
 * Each game will inherit to make GSoundPlayer and implement
 * the pure virtual methods.
 */


class GSoundPlayer : public BBase {

public:
  GSoundPlayer();
  ~GSoundPlayer();

public:
  TUint8 mMusicVolume;
  TUint8 mEffectsVolume;
  TBool mMuted;
  TBool mAudioPaused;
  TInt16 mCurrentSongLoaded;
  TUint8 mNumberFxChannels;
  TUint8 mNumberFxSlots;

public:
  void Init(TUint8 aNumberFxChannels, TUint8 aNumberFxSlots);


//   // set system volume
  TBool SetVolume(TFloat aPercent);
  TBool SetMusicVolume(TFloat aPercent);
  TBool SetEffectsVolume(TFloat aPercent);
//   // mute or unute sounds & music (MASTER mute)
//   virtual TBool Mute(TBool aMuted = ETrue) = 0;
// public:
//   // play a sound, overriding an existing sound with lower priority (if necessary)
//   // sound will loop back to start if flag is set
  TBool PlaySound(TInt aSoundNumber, TInt aPriority, TBool aLoop = EFalse);
//   // stop a currently playing sound
//   virtual TBool StopSound(TInt aSoundNumber) = 0;
//   // mute only sound effects (music will continue to be heard)
//   virtual TBool MuteSounds(TBool aMuted = ETrue) = 0;
//   // stop all sounds (but not music)
//   virtual TBool StopSounds() = 0;
// public:
//   // play a song, track will loop back to start if flag is set
//   // if a score is already playing, it will be stopped first
  TBool PlayMusic(TInt16 aResourceId);

  TBool LoadEffect(TUint16 aResourceId, TUint8 aSlotNumber);

//   //  stop playing music
  TBool StopMusic();

//   // toggle music paused/playing

//   // toggle music muted (will not mute sound effects)
// public:
//   // reset music player, stop all sounds and music
  TBool Reset();

  TBool MuteMusic(TBool aMuted = ETrue) {

    audio.Mute(mMuted = aMuted);
    return true;
  }
  TBool PauseMusic(TBool aPaused = ETrue) {
    mAudioPaused = aPaused;
    return true;
  }

};


extern GSoundPlayer soundPlayer;

#endif //GSOUNDPLAYER_H
