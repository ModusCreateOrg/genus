#include "Game.h"
#include "GSoundPlayer.h"
#include "GResources.h"
#include "Memory.h"

#define DISABLE_AUDIO
#undef DISABLE_AUDIO


GSoundPlayer gSoundPlayer;

static const TUint16 effectsList[] = {
  SFX_GOOD_DROP_BLOCK_WAV,
  SFX_BAD_DROP_BLOCK_WAV,
  SFX_MOVE_BLOCK_WAV,
  SFX_ROTATE_BLOCK_LEFT_WAV,
  SFX_ROTATE_BLOCK_RIGHT_WAV,
  SFX_SCORE_COMBO_WAV,
  SFX_OPTION_SELECT_WAV,
  SFX_EXPLODE_BLOCK_WAV,
  SFX_NEXT_LEVEL_WAV,
  SFX_NEXT_STAGE_WAV,
  SFX_SAVE_GAME_WAV
};

static const TUint16 allSongs[] = {
  EMPTYSONG_XM,
  UNDER_WATER_XM,
  CYBERPUNK_XM,
  COUNTRYSIDE_XM,
  MAIN_MENU_XM,
  SPAAACE_XM,
  GLACIAL_MOUNTAINS_XM,
  GAMEOVER_XM,
  UNDERWATERFANTASY_XM,
  GAMEOVER_XM,
  ENTERCREDITS_XM
};

static TUint16 FindSfxNumber(TUint16 aSfxFile) {

  for (size_t i = 0; i < sizeof(effectsList); i++) {
    if (aSfxFile == effectsList[i]) {
      return (TUint16) i; // Should not go above UINT16_MAX
    }
  }
  printf("WARNING :: Could not find SFX for ID %i\n", aSfxFile);


  return UINT16_MAX;
}


GSoundPlayer::~GSoundPlayer() {
  // Release songs memory
  FreeMem(mSongSlots);
}

void GSoundPlayer::Init(TUint8 aNumberFxChannels) {
  mMaxSongs = sizeof(allSongs) / sizeof(TUint16);
  mMaxEffects = sizeof(effectsList) / sizeof(TUint16);

  soundEngine.InitAudioEngine(aNumberFxChannels, mMaxEffects);

//  SDL_ClearError();
  LoadEffects();
//  SDL_ClearError();



  mSongSlots = (SongSlot *)AllocMem(sizeof(SongSlot) * mMaxSongs, MEMF_SLOW);

//  for (TUint8 i = 0; i < mMaxSongs; i++) {
//    auto *slot = (SongSlot *)AllocMem(sizeof(SongSlot), MEMF_SLOW);
//
//    slot->mResourceNumber = allSongs[i];
//    slot->mSlotNumber = SONG0_SLOT + i;
//
//    gResourceManager.LoadRaw(allSongs[i], slot->mSlotNumber);
//    slot->mRaw = gResourceManager.GetRaw(slot->mSlotNumber);
//
//    mSongSlots[i] = *slot;
//    FreeMem(slot);
//  }
  PlayMusic(EMPTYSONG_XM);


  soundEngine.SetMusicVolume(gOptions->music);
  soundEngine.SetEffectsVolume(gOptions->sfx);
  soundEngine.MuteMusic(gOptions->muted);
}

TBool GSoundPlayer::PlayMusic(TInt16 aResourceId) {
  //  aResourceId = EMPTYSONG_XM;
//  printf("%s %i\n", __PRETTY_FUNCTION__, aResourceId);

  BRaw *songToLoad = FindRawSongFileById(aResourceId);

  TBool music = soundEngine.PlayMusic(songToLoad, aResourceId);
//   BSoundEngine::PlayMusic un-mutes the music
// We have to re-mute it in case of mute == true

  soundEngine.SetMusicVolume(gOptions->music);
  soundEngine.SetEffectsVolume(gOptions->sfx);
  soundEngine.MuteMusic(gOptions->muted);

  return music;
}


BRaw *GSoundPlayer::FindRawSongFileById(TInt16 aResourceId) {

  for (TUint8 i = 0; i < mMaxSongs; i++) {
    if (allSongs[i] == aResourceId) {
      if (gResourceManager.GetRaw(SONG0_SLOT)) {
        gResourceManager.ReleaseRawSlot(SONG0_SLOT);
      }
      gResourceManager.LoadRaw(allSongs[i], SONG0_SLOT);
      return gResourceManager.GetRaw(SONG0_SLOT);;
    }
  }

  printf("WARNING :: Could not find song %i\n", aResourceId);

  return ENull;
}


TBool GSoundPlayer::LoadEffects() {
  for (TUint8 index = 0; index < mMaxEffects; index++) {
    soundEngine.LoadEffect(index, effectsList[index], SFX1_SLOT + index);
//    return ETrue;
  }
  return ETrue;
}


void  GSoundPlayer::MuteMusic(TBool aMuted) {
  return soundEngine.MuteMusic(aMuted);
}



void GSoundPlayer::TriggerSfx(TUint16 aSfxNumber, TInt8 aChannel) {
  soundEngine.PlaySfx(FindSfxNumber(aSfxNumber), aChannel);
}


void GSoundPlayer::SfxGoodDrop() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_GOOD_DROP_BLOCK_WAV), 1);
}

void GSoundPlayer::SfxRotateRight() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_ROTATE_BLOCK_RIGHT_WAV), 1);
}

void GSoundPlayer::SfxRotateLeft() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_ROTATE_BLOCK_LEFT_WAV), 1);
}

void GSoundPlayer::SfxBadDrop() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_BAD_DROP_BLOCK_WAV), 1);
}

void GSoundPlayer::SfxCombo() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_SCORE_COMBO_WAV), 1);
}

void GSoundPlayer::SfxMoveBlock() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_MOVE_BLOCK_WAV), 1);
}

void GSoundPlayer::SfxExplodeBlock() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_EXPLODE_BLOCK_WAV), 1);
}

void GSoundPlayer::SfxOptionSelect() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_OPTION_SELECT_WAV), 1);
}

void GSoundPlayer::SfxMenuNavUp() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_ROTATE_BLOCK_LEFT_WAV), 2);
}

void GSoundPlayer::SfxMenuNavDown() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_ROTATE_BLOCK_RIGHT_WAV), 2);
}

void GSoundPlayer::SfxMenuAccept() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_GOOD_DROP_BLOCK_WAV), 1);
}

void GSoundPlayer::SfxMenuCancel() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_GOOD_DROP_BLOCK_WAV), 1);
}

void GSoundPlayer::SfxNextLevel() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_NEXT_LEVEL_WAV), 3);
}

void GSoundPlayer::SfxNextStage() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_NEXT_LEVEL_WAV), 2);
}

void GSoundPlayer::SfxSaveGame() {
  soundEngine.PlaySfx(FindSfxNumber(SFX_SAVE_GAME_WAV), 1);
}