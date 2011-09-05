// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef AUDIO_H
#define AUDIO_H

#define MUSIC_CHANNEL (PSPAALIB_CHANNEL_SCEMP3_1)
#define SOUND_CHANNEL (PSPAALIB_CHANNEL_WAV_1)
#define CURRENT_SOUND (SOUND_CHANNEL+sound_nbr-1)
#define MAX_SOUNDS (32)

extern char sound_name[MAX_SOUNDS][128];
extern int sound_nbr;

void setMusic(const char* path); // MP3 cbr only
void loadSound(const char* path, const char* name); // Wav only
void freeSound(const char* name);
void playSound(const char* name);
void initAudio();

#endif
