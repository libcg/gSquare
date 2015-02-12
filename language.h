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

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "common.h"
#include "game.h"

typedef struct
{
  char title[MENU_TITLE_NBR][128];
  char story[3][128];
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
