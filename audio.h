// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef AUDIO_H
#define AUDIO_H

#define MAX_SOUNDS (16)

extern char sound_name[MAX_SOUNDS][128];

void setMusic(const char* path); // MP3 cbr only
void loadSound(const char* path, const char* name); // Wav only
void freeSound(const char* name);
void playSound(const char* name);
void initAudio();

#endif
