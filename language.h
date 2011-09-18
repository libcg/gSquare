// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "common.h"
#include "game.h"

typedef struct
{
  char title[MENU_TITLE_NBR][128];
  char story[2][128];
  char config[3][128];
  char config_setting[3][128];
} Menu_Text;

typedef struct
{
  char pause[128];
  char pause_choice[PAUSE_CHOICE_NBR][128];
  char win[128];
  char next_level[128];
  char time_over[128];
  char respawn[128];
  char out_bounds[128];
  char death[128];
} Game_Text;

typedef struct
{
  Menu_Text menu;
  Game_Text game;
  char credits[1024];
  char authors[128];
  char website[128];
} Text;

extern Text text;
extern int lang_n;

void initLanguage();
void loadLanguage();

#endif
