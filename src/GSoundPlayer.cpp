//
// Created by Jesus Garcia on 10/2/18.
//

#include "GSoundPlayer.h"
#include "GResources.h"


GSoundPlayer gSoundPlayer;

#include "libxmp/xmp.h"


#ifdef __XTENSA__

#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include <string.h> // For memset

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

#endif



#ifdef __XTENSA__

#define SAMPLE_RATE (22050)

#else

#define SAMPLE_RATE (44100)

#endif

#define TIMER_LENGTH 50
#define AUDIO_BUFF_SIZE 12

xmp_context xmpContext;

bool musicFileLoaded = false;

// Prototype static prototype methods
static int loadSong(BRaw *aSong);

GSoundPlayer::GSoundPlayer() {
  xmpContext = xmp_create_context();

  mMusicVolume = 16;
  mEffectsVolume = 16;
  mMuted = false;
  mAudioPaused = false;
  mRowNumber = 0;
  mPatternNumber = 0;
}

GSoundPlayer::~GSoundPlayer() {
  Reset();
  xmp_end_player(xmpContext);
#ifndef __XTENSA__
  //TODO: Tear down SDL
#endif
}

bool WARNED_OF_PLAY_BUFFER = false;

static void fillBuffer(void *audioBuffer, size_t length) {
  if (musicFileLoaded && ! gSoundPlayer.mAudioPaused) {
    int result = xmp_play_buffer(xmpContext, audioBuffer, length, 0);

    struct xmp_frame_info frameInfo;


    if (result != 0) {
      if (!WARNED_OF_PLAY_BUFFER) {
        // Something really bad happened, and audio stopped :(
        printf("xmp_play_buffer not zero (result = %i)!\n", result);fflush(stdout);
        WARNED_OF_PLAY_BUFFER = true;
      }
      memset(audioBuffer, 0, length);
    }
  }
  else {
    memset(audioBuffer, 0, length);
  }

#ifndef __XTESNA__
  
  if (audio.IsMuted()) {
    memset(audioBuffer, 0, length);
  }
#endif
}


#ifdef __XTENSA__

// ESP32 style timer
static void timerCallback(void *arg) {
  fillBuffer(audio.mAudioBuffer, AUDIO_BUFF_SIZE);
  // Need to submit to the audio driver.
  audio.Submit(audio.mAudioBuffer, AUDIO_BUFF_SIZE >> 2);
}

#else

// SDL style timer
static void timerCallback(void *udata, Uint8 *audioBuffer, int length) {
  fillBuffer(audioBuffer, length);
}

#endif


void GSoundPlayer::Init(TUint8 aNumberFxChannels, TUint8 aNumberFxSlots) {
  audio.Init(&timerCallback);



  #ifndef __XTENSA__
  // Kick off SDL audio engine
  SDL_PauseAudio(0);
  #endif


  mNumberFxChannels = aNumberFxChannels;
  mNumberFxSlots = aNumberFxSlots;
}

static int loadSong(BRaw *aSong) {
  int loadResult = xmp_load_module_from_memory(xmpContext, aSong->mData, aSong->mSize);
//  printf("xmp_load_module_from_memory result = %i\n", loadResult); fflush(stdout);
  return loadResult;
}


TBool GSoundPlayer::LoadEffect(TUint16 aResourceId, TUint8 aSlotNumber) {
  gResourceManager.LoadRaw(aResourceId, SONG_SLOT);
  BRaw *effect = gResourceManager.GetRaw(SONG_SLOT);

//  printf("LoadEffect slot=%i, size=%i\n", aSlotNumber, effect->mSize);
  int result = xmp_smix_load_sample_from_memory(xmpContext, aSlotNumber, effect->mData, effect->mSize);
//  printf("xmp_smix_load_sample_from_memory result = %i\n", result);

  gResourceManager.ReleaseRawSlot(SONG_SLOT);

  return result == 0;
}

void loadEffects() {

  const uint16_t effectsList[] = {
    SFX_BOSS_EXPLODE_WAV,
    SFX_ENEMY_EXPLODE_WAV,
    SFX_ENEMY_FLYBY_WAV,
    SFX_ENEMY_SHOOT_WAV,
    SFX_NEXT_ATTRACT_CHAR_WAV,
    SFX_NEXT_ATTRACT_SCREEN_WAV,
    SFX_PLAYER_HIT_WAV,
    SFX_PLAYER_SHOOT_WAV,
    SFX_SPEED_BOOST_WAV,
  };

  for (uint8_t i = 0; i < 9; i++) {
    gSoundPlayer.LoadEffect(effectsList[i], i);
  }

}


bool SMIX_INITIALIZED = false;

TBool GSoundPlayer::PlayMusic(TInt16 aResourceId) {

  if (aResourceId == mCurrentSongLoaded) {
    return false;
  }
#ifndef __XTENSA__
//  SDL_PauseAudio(1);
#endif
  printf("PlayMusic(%i);\n", aResourceId); fflush(stdout);

  audio.Mute(true);
  musicFileLoaded = false;
  MuteMusic(ETrue);
  PauseMusic(true);

  xmp_stop_module(xmpContext);

  gResourceManager.LoadRaw(aResourceId, SONG_SLOT);
  BRaw *song = gResourceManager.GetRaw(SONG_SLOT);

  xmp_set_player(xmpContext, XMP_PLAYER_VOLUME, 0);

  int loadResult = loadSong(song);
  if (loadResult < 0) {
    // Sometimes XMP fails for no obvious reason. Try one more time for good measure.
    loadResult = loadSong(song);
  }

  if (loadResult == 0) {
    musicFileLoaded = true;
    mCurrentSongLoaded = aResourceId;
  }

  gResourceManager.ReleaseRawSlot(SONG_SLOT);

  if (!musicFileLoaded) {
    printf("MUSIC LOADING FAILED!\n"); fflush(stdout);
    return EFalse;
  }

  // Every time a new song is loaded, we must load sound effects too!
  xmp_start_smix(xmpContext, mNumberFxChannels, mNumberFxSlots);
  loadEffects();

  xmp_start_player(xmpContext, SAMPLE_RATE, 0);
  xmp_set_player(xmpContext, XMP_PLAYER_VOLUME, mMusicVolume);
  xmp_set_player(xmpContext, XMP_PLAYER_SMIX_VOLUME, 64); //Volume is governed globally via mEffectsVolume
  xmp_set_player(xmpContext, XMP_PLAYER_MIX, 0);


  MuteMusic(EFalse);
  PauseMusic(false);
  audio.Mute(false);

#ifndef __XTENSA__
//  SDL_PauseAudio(0);
#endif
  return ETrue;
}


TUint8 sfxChannel = 0;

TBool GSoundPlayer::StopMusic() {
  // Should we test for XMP_STATE_UNLOADED, XMP_STATE_PLAYING?
  xmp_stop_module(xmpContext);
  return true;
}

TBool GSoundPlayer::Reset() {
  StopMusic();
//  xmp_end_player(xmpContext);
  musicFileLoaded = false;
  return true;
}

TBool GSoundPlayer::SetVolume(TFloat aPercent) {
  if (xmpContext) {
    if (aPercent > 1.0f) {
      aPercent = 1.0f;
    }

    if (aPercent < 0.0f) {
      aPercent = 0;
    }

    mMusicVolume = (TUint8)(aPercent * 255);
    mEffectsVolume = mMusicVolume;

    xmp_set_player(xmpContext, XMP_PLAYER_VOLUME, mMusicVolume);
    return true;
  }

  return false;
}

TBool GSoundPlayer::SetMusicVolume(TFloat aPercent) {
  if (xmpContext) {
    if (aPercent > 1.0f) {
      aPercent = 1.0f;
    }
    if (aPercent < 0.0f) {
      aPercent = 0;
    }

    mMusicVolume = (TUint8)(aPercent * 255);

    xmp_set_player(xmpContext, XMP_PLAYER_VOLUME, mMusicVolume);
    return true;
  }

  return false;
}

TBool GSoundPlayer::SetEffectsVolume(TFloat aPercent) {
  if (xmpContext) {
    if (aPercent > 1.0f) {
      aPercent = 1.0f;
    }

    if (aPercent < 0.0f) {
      aPercent = 0;
    }

    mEffectsVolume = (TUint8)(aPercent * 255);
    xmp_set_player(xmpContext, XMP_PLAYER_SMIX_VOLUME, mEffectsVolume);
    return true;
  }

  return false;
}



TBool GSoundPlayer::PlaySound(TInt aSoundNumber, TInt aPriority, TBool aLoop) {
  //Todo: priority?
  if (! musicFileLoaded) {
    printf("No Music file loaded\n");
    return false;
  }

  xmp_smix_play_sample(xmpContext, aSoundNumber, 60, mEffectsVolume, sfxChannel);

  sfxChannel++;
  if (sfxChannel >= 3) {
    sfxChannel = 0;
  }
  return true;
}
