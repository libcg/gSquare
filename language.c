// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "config.h"
#include "language.h"

Text text;
int lang_n = 0;
char** lang_list = NULL;

void getLanguageList()
{
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
  
  if (cfg.lang_id >= lang_n)
  {
    throwException("Wrong language id\n");
    return;
  }
}



void loadLanguage()
{
  char path[256] = {0};
  sprintf(path,"lang/%s.lng",lang_list[cfg.lang_id]);
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
  fscanf(file,"%[^\n]\n",text.game.out_bounds);
  fscanf(file,"%[^\n]\n",text.game.death);
  
  strcpy(text.credits,
"gSquare\n\nBy meastnt and Geecko\nDesign by Maxime Brugnon and CaptainKill\nMu\
sic by c418 (mainly from Little Things)\nTesting by Léo, Arthur, Baptiste, Maxi\
me\n\nUsing :\nGraphics library - gLib2D by Geecko\nFont library - intraFont-G \
by BenHur\nAudio library - aalib by Arshia001\nPSPSDK - ps2dev.org\n\nThanks to\
:\nFrench PSP community (PSP-Gen, XtreamLua)\nSony for his marvellous developme\
nt platform");
  strcpy(text.authors,"Presented by meastnt and Geecko");
  strcpy(text.website,"http://sites.google.com/site/gsquarecenter");
  sprintf(text.menu.config_setting[0],"%d%%",cfg.music_vol);
  sprintf(text.menu.config_setting[1],"%d%%",cfg.sound_vol); 

  fclose(file);
}

void initLanguage()
{
  getLanguageList();
  loadLanguage();
}  

// EOF
