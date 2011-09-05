// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <stdio.h>

#include "config.h"

Config cfg = {100,100,0};

void configSave()
{
  FILE* file = fopen(CONFIG_PATH,"w");
  if (file == NULL) return;
  
  fprintf(file,"%d %d\n",cfg.music_vol,cfg.sound_vol);
  fprintf(file,"%d\n",cfg.lang_id);
  
  fclose(file);
}


void configLoad()
{
  FILE* file = fopen(CONFIG_PATH,"r");
  if (file == NULL) return;
  
  fscanf(file,"%d %d\n",&cfg.music_vol,&cfg.sound_vol);
  fscanf(file,"%d\n",&cfg.lang_id);
  
  fclose(file);
}

// EOF
