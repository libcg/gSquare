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
  char config[2][128];
  char config_setting[2][128];
} Menu_Text;

typedef struct
{
  char title[128];
  char choice[PAUSE_CHOICE_NBR][128];
} Pause_Text;

typedef struct
{
  Menu_Text menu;
  Pause_Text pause;
  char credits[16384];
} Text;

extern Text text;

void initLanguage();

#endif
