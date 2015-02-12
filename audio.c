/*
 * This file is part of gSquare.
 *
 * gSquare is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gSquare is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gSquare.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SDL.h>
#include <SDL_mixer.h>

#include "audio.h"
#include "common.h"
#include "config.h"
#include "controls.h"

typedef struct
{
  char name[128];
  Mix_Chunk *chunk;
} Sound;

float global_volume = 0.f;
char music_path[128] = "!", music_old_path[128] = "!";
Sound sound[MAX_SOUNDS];
int sound_nbr = 0, music_fade = 0;

static void musicLogic()
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
    Mix_PauseMusic();
    if (music_path[0] != '!')
    {
      music_fade = 1;

      Mix_Music *music = Mix_LoadMUS(music_path);
      if (music == NULL)
      {
        throwException("Failed to load the music: %s",Mix_GetError());
      }

      if (Mix_PlayMusic(music, 1) != 0)
      {
        throwException("Failed to play the music: %s",Mix_GetError());
      }
    }
  }

  if (global_volume > 0.f)
  {
    Mix_ResumeMusic();
    Mix_VolumeMusic(MIX_MAX_VOLUME * global_volume * cfg.music_vol / 100.f);
  }
}

// Streamed music

void setMusic(const char* path)
{
  if (cfg.music_vol == 0) Mix_HaltMusic();
  if (path == NULL) throwException("NULL music path");
  if (strcmp(path,music_old_path) != 0)
  {
    strncpy(music_path,path,128);
    if (path[0] != '!') strncpy(music_old_path,path,128);
    music_fade = -1;
  }
  else // Same music as before
  {
    music_fade = 1;
  }
}

// Sounds

static int getSoundId(const char* name)
{
  int i;

  for (i=0; i!=sound_nbr; i++)
  {
    if (strcmp(sound[i].name,name) == 0) return i;
  }

  return -1;
}


void loadSound(const char* path, const char* name)
{
  if (getSoundId(name) >= 0) return;
  if (sound_nbr == MAX_SOUNDS) throwException("Too many sounds loaded !\n");

  strncpy(sound[sound_nbr].name,name,128);
  sound[sound_nbr].chunk = Mix_LoadWAV(path);

  if (!sound[sound_nbr].chunk)
  {
    throwException("Failed to load the sound ! (error = %d)\n",Mix_GetError());
  }

  sound_nbr++;
}


void freeSound(const char* name)
{
  int id = getSoundId(name);

  if (id >= 0)
  {
    Mix_FreeChunk(sound[id].chunk);
  }
}


void playSound(const char* name)
{
  int id = getSoundId(name);

  if (id >= 0 && cfg.sound_vol > 0) {
    Mix_VolumeChunk(sound[id].chunk,
                    MIX_MAX_VOLUME * global_volume * cfg.sound_vol / 100);
    Mix_PlayChannel(id, sound[id].chunk, 0);
  }
}


void clearSound()
{
  while (--sound_nbr > 0)
  {
    Mix_FreeChunk(sound[sound_nbr].chunk);
  }
}

// General audio

int audioThread(void *args)
{
  SDL_InitSubSystem(SDL_INIT_AUDIO);

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096))
  {
	throwException("Unable to initialize audio: %s\n", Mix_GetError());
  }

  loadSound("./audio/death.wav","death");
  loadSound("./audio/jump.wav","jump");
  loadSound("./audio/break.wav","break");

  while (!exit_state)
  {
    musicLogic();

    SDL_Delay(1000/FPS);
  }

  setMusic("!");

  return 0;
}


void initAudio()
{
  // Start audio thread
  SDL_CreateThread(audioThread, "audio_thread", NULL);
}

// EOF
