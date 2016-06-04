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
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "language.h"

Text text;
int lang_n = 0;
char** lang_list = NULL;

void getLanguageList()
{
  Config *cfg = configGet();
  FILE* file = fopen("lang/list","r");
  if (file == NULL)
  {
    throwException("Unable to open language list file\n");
    return;
  }

  lang_n = 0;
  do
  {
    lang_list = realloc(lang_list,(++lang_n)*sizeof(char*));
    lang_list[lang_n-1] = malloc(16*sizeof(char));
  }
  while (fscanf(file,"%[^\n]\n",lang_list[lang_n-1]) > 0);

  fclose(file);
  lang_n--;

  if (cfg->lang_id >= lang_n)
  {
    throwException("Wrong language id\n");
    return;
  }
}



void loadLanguage()
{
  Config *cfg = configGet();
  char path[256];
  sprintf(path,"lang/%s.lng",lang_list[cfg->lang_id]);
  FILE* file = fopen(path,"r");

  fscanf(file,"%[^\n]\n\n",text.menu.config_setting[2]);
  // Menu
  fscanf(file,"%[^\n]\n",text.menu.title[0]);
  fscanf(file,"%[^\n]\n",text.menu.title[1]);
  fscanf(file,"%[^\n]\n",text.menu.title[2]);
  fscanf(file,"%[^\n]\n",text.menu.title[3]);
  fscanf(file,"%[^\n]\n",text.menu.story[0]);
  fscanf(file,"%[^\n]\n",text.menu.story[1]);
  fscanf(file,"%[^\n]\n",text.menu.story[2]);
  fscanf(file,"%[^\n]\n",text.menu.config[0]);
  fscanf(file,"%[^\n]\n",text.menu.config[1]);
  fscanf(file,"%[^\n]\n",text.menu.config[2]);
  fscanf(file,"%[^\n]\n",text.menu.config[3]);
  // Game
  fscanf(file,"%[^\n]\n",text.game.pause);
  fscanf(file,"%[^\n]\n",text.game.pause_choice[0]);
  fscanf(file,"%[^\n]\n",text.game.pause_choice[1]);
  fscanf(file,"%[^\n]\n",text.game.pause_choice[2]);
  fscanf(file,"%[^\n]\n",text.game.pause_choice[3]);
  fscanf(file,"%[^\n]\n",text.game.win);
  fscanf(file,"%[^\n]\n",text.game.next_level);
  fscanf(file,"%[^\n]\n",text.game.time_over);
  fscanf(file,"%[^\n]\n",text.game.respawn);
  // General
  fscanf(file,"%[^\n]\n",text.yes);
  fscanf(file,"%[^\n]\n",text.no);

  strcpy(text.credits,
    "\n\ngSquare\n\n"
    "Game engine: libcg\n"
    "Gameplay, level design: meastnt\n"
    "Design: Maxime Brugnon, CaptainKill\n"
    "Music: c418 (mainly from Little Things)\n\n"
    "Originally released on the Playstation Portable");
  strcpy(text.authors,"Presented by @meastnt and @libcg");
  strcpy(text.website,"https://github.com/libcg/gsquare");

  sprintf(text.menu.config_setting[0],"%d%%",cfg->music_vol);
  sprintf(text.menu.config_setting[1],"%d%%",cfg->sound_vol);
  sprintf(text.menu.config_setting[3],"%s",
    cfg->fullscreen ? text.yes : text.no);

  fclose(file);
}

void initLanguage()
{
  getLanguageList();
  loadLanguage();
}

// EOF
