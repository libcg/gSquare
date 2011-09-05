// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <pspdisplay.h>

#include "audio.h"
#include "common.h"
#include "config.h"

#include "./lib/pspaalib.h"

float global_volume = 0.f, music_fade = 0;
char music_path[128] = "!", music_old_path[128] = "!";
char sound_name[MAX_SOUNDS][128];
int sound_nbr = 0;

// Streamed music

void setMusic(const char* path)
{
  #ifdef DEBUG
    return;
  #endif
  if (cfg.music_vol == 0) AalibStop(MUSIC_CHANNEL);
  if (path == NULL) throwException("NULL music path");
  if (strcmp(path,music_old_path) != 0)
  {
    strncpy(music_path,path,128);
    if (path[0] != '!') strncpy(music_old_path,path,128);
    music_fade = -1;
  }
  else if (music_path[0] == '!')
  {
    AalibPlay(MUSIC_CHANNEL);
    music_fade = 1;
  }
}


void musicStuff()
{
  global_volume += music_fade * FADE_TIME / FPS;
  if (music_fade > 0 && global_volume > 1.f)
  {
    music_fade = 0;
    global_volume = 1.f;
  }
  else if (music_fade < 0 && global_volume < 0.f)
  {
    music_fade = 0;
    global_volume = 0.f;
    AalibPause(MUSIC_CHANNEL);
    if (music_path[0] != '!')
    {
      music_fade = 1;
      AalibUnload(MUSIC_CHANNEL);
      int err = AalibLoad(music_path,MUSIC_CHANNEL,0);
      if (err > 0)
      {
        throwException("Failed to load the music ! (error = %d)\n",err);
      }
      else
      {
        AalibSetAutoloop(MUSIC_CHANNEL,1);
        AalibPlay(MUSIC_CHANNEL);
      }
    }
  }
  
  AalibVolume vol = {global_volume * (cfg.music_vol / 100.f),
                     global_volume * (cfg.music_vol / 100.f)};
  AalibEnable(MUSIC_CHANNEL,PSPAALIB_EFFECT_VOLUME_MANUAL);
  AalibSetVolume(MUSIC_CHANNEL,vol);
}

// Sounds

int getSoundID(const char* name)
{
  int i;
  for (i=0; i!=sound_nbr; i++)
  {
    if (strcmp(sound_name[i],name) == 0) break;
  }
  if (i == sound_nbr)
  {
    throwException("Sound name not found !\n");
    return -1;
  }  
  return i;
}


void loadSound(const char* path, const char* name)
{
  #ifdef DEBUG
    return;
  #endif
  if (sound_nbr == MAX_SOUNDS) throwException("Too much sounds loaded !\n");
  
  sound_nbr++;
  strncpy(sound_name[sound_nbr-1],name,128);
  int err = AalibLoad((char*)path,CURRENT_SOUND,1);
  if (err > 0)
  {
    throwException("Failed to load the sound ! (error = %d)\n",err);
  }
}


void freeSound(const char* name)
{
  #ifdef DEBUG
    return;
  #endif
  int id = getSoundID(name);
  AalibStop(SOUND_CHANNEL+id);
  AalibUnload(SOUND_CHANNEL+id);
}


void playSound(const char* name)
{
  #ifdef DEBUG
    return;
  #endif
  if (cfg.sound_vol == 0) return;
  
  AalibVolume vol = {global_volume * (cfg.sound_vol / 100.f),
                     global_volume * (cfg.sound_vol / 100.f)};

  int id = getSoundID(name);
  AalibRewind(SOUND_CHANNEL+id);
  AalibPlay(SOUND_CHANNEL+id);
  AalibEnable(SOUND_CHANNEL+id,PSPAALIB_EFFECT_VOLUME_MANUAL);
  AalibSetVolume(SOUND_CHANNEL+id,vol);
}


void clearSound()
{
  #ifdef DEBUG
    return;
  #endif
  while (--sound_nbr > 0)
  {
    AalibStop(SOUND_CHANNEL+sound_nbr);
    AalibUnload(SOUND_CHANNEL+sound_nbr);    
  } 
}

// General audio

int audioThread(SceSize args, void *argp)
{
  sceIoChdir(cwd);
  
  while (!exit_state)
  {
    musicStuff();  
    
    sceDisplayWaitVblankStart();
  }
  
  setMusic("!");
  
  return 0;
}


void initAudio()
{
  #ifdef DEBUG
    return;
  #endif
  AalibInit();
  loadSound("./audio/death.wav","death");
  loadSound("./audio/jump.wav","jump");
  loadSound("./audio/break.wav","break");
  // Start audio thread
  SceUID thid = sceKernelCreateThread("audio_thread",audioThread,0x11,0x30000,
                                      THREAD_ATTR_USER | THREAD_ATTR_VFPU,NULL);
  if (thid < 0)
  {
    throwException("Can't create the audio thread\n");
  }
  if (sceKernelStartThread(thid,0,0))
  {
    throwException("Can't start the audio thread\n");
  }
}

// EOF
