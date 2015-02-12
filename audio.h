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
