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
