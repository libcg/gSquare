// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_PATH "config"

typedef struct
{
  int music_vol, sound_vol;
  int lang_id;
} Config;

extern Config cfg;

void configSave();
void configLoad();

#endif
