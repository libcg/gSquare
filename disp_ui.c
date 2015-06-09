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
#include "game.h"
#include "disp.h"
#include "controls.h"
#include "common.h"
#include "level.h"
#include "audio.h"
#include "language.h"

#include "lib/glib2d.h"
#include "lib/glib2d_font.h"

Fade ui_fade = {FADE_OUT,0.f,3.5f,255,0,0.f,BLACK};
g2dColor timer_back_color = WHITE;
float timer_size = 1.f;
int dcount = 0;

void setTimerAspect(float size, g2dColor color)
{
  if (size >= 0.f) timer_size = size;
  timer_back_color = color;
}


void drawUI()
{
  if (dcount++ > DCOUNT_MAX) dcount = 0;

  drawFade(&ui_fade);

  // Timer
  timer_size += (1.f-timer_size) * TIMER_SIZE_SPEED;
  timer_back_color = G2D_RGBA(G2D_GET_R(timer_back_color) +
                              (int)((255-G2D_GET_R(timer_back_color))*TIMER_SIZE_SPEED),
                              G2D_GET_G(timer_back_color) +
                              (int)((255-G2D_GET_G(timer_back_color))*TIMER_SIZE_SPEED),
                              G2D_GET_B(timer_back_color) +
                              (int)((255-G2D_GET_B(timer_back_color))*TIMER_SIZE_SPEED),
                              255);

  if (getGameState() == INGAME || getGameState() == LOSE)
  {
    ui_fade.mode = FADE_OUT;
    cam.zoom_target = 1.9f;
    // Timer
    char timer_text[32];
    sprintf(timer_text,"%.2d:%.2d",game.time_elapsed/60,game.time_elapsed%60);
    g2dFontBegin(bigfont, timer_text);
    {
      g2dFontSetCoordMode(G2D_CENTER);
      g2dFontSetCoordXY(g2dScrW()/2,25);
      g2dFontSetScale(timer_size);
      g2dFontSetColor(timer_back_color);
      g2dFontSetCoordXYRelative(1, 1);
      g2dFontAdd();
      g2dFontSetCoordXYRelative(0, -2);
      g2dFontAdd();
      g2dFontSetCoordXYRelative(-2, 0);
      g2dFontAdd();
      g2dFontSetCoordXYRelative(0, 2);
      g2dFontAdd();
      g2dFontSetColor(BLACK);
      g2dFontSetCoordXYRelative(1, -1);
      g2dFontAdd();
    }
    g2dFontEnd();
    // Flying text
    if (game.flying_text != NULL)
    {
      g2dFontBegin(font, game.flying_text);
      {
        g2dFontSetCoordMode(G2D_CENTER);
        g2dFontSetCoordXY(g2dScrW()/2,g2dScrH()-25);
        g2dFontSetColor(WHITE);
        g2dFontSetCoordXYRelative(1, 1);
        g2dFontAdd();
        g2dFontSetCoordXYRelative(0, -2);
        g2dFontAdd();
        g2dFontSetCoordXYRelative(-2, 0);
        g2dFontAdd();
        g2dFontSetCoordXYRelative(0, 2);
        g2dFontAdd();
        g2dFontSetColor(BLACK);
        g2dFontSetCoordXYRelative(1, -1);
        g2dFontAdd();
      }
      g2dFontEnd();
    }
  }
  else if (getGameState() == WIN)
  {
    ui_fade.color = WHITE;
    ui_fade.max = 255;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 3.f;
    g2dFontBegin(bigfont, text.game.win);
    {
      g2dFontSetCoordMode(G2D_CENTER);
      g2dFontSetCoordXY(g2dScrW()/2,g2dScrH()/2);
      g2dFontSetScale(0.9f);
      g2dFontSetColor(BLACK);
      g2dFontAdd();
    }
    g2dFontEnd();
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      g2dFontBegin(font, text.game.next_level);
      {
        g2dFontSetCoordMode(G2D_DOWN_RIGHT);
        g2dFontSetCoordXY(g2dScrW()-15,g2dScrH()-15);
        g2dFontSetAlpha(255*dcount/DCOUNT_MAX);
        g2dFontSetScale(0.9f);
        g2dFontSetColor(BLACK);
        g2dFontAdd();
      }
      g2dFontEnd();
    }
  }
  else if (getGameState() == TIME_OVER)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 255;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 1.f;
    g2dFontBegin(bigfont, text.game.time_over);
    {
      g2dFontSetCoordMode(G2D_CENTER);
      g2dFontSetCoordXY(g2dScrW()/2,g2dScrH()/2);
      g2dFontSetScale(0.9f);
      g2dFontSetColor(WHITE);
      g2dFontAdd();
    }
    g2dFontEnd();
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      g2dFontBegin(font, text.game.respawn);
      {
        g2dFontSetCoordMode(G2D_DOWN_RIGHT);
        g2dFontSetCoordXY(g2dScrW()-15,g2dScrH()-15);
        g2dFontSetAlpha(255*dcount/DCOUNT_MAX);
        g2dFontSetScale(0.9f);
        g2dFontSetColor(WHITE);
        g2dFontAdd();
      }
      g2dFontEnd();
    }
  }
  else if (getGameState() == PAUSE)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 127;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 0.85f;
    g2dFontBegin(bigfont, text.game.pause);
    {
      g2dFontSetCoordMode(G2D_CENTER);
      g2dFontSetCoordXY(g2dScrW()/2,g2dScrH()/2);
      g2dFontSetScale(0.9f);
      g2dFontSetColor(WHITE);
      g2dFontAdd();
    }
    g2dFontEnd();

    int i;
    for (i=0; i!=PAUSE_CHOICE_NBR; i++)
    {
      g2dFontBegin(font, text.game.pause_choice[i]);
      {
        g2dFontSetCoordMode(G2D_DOWN_RIGHT);
        g2dFontSetCoordXY(g2dScrW()-15,g2dScrH()-5-25*i);
        g2dFontSetAlpha(127+(pause.i==i ? dcount*127/DCOUNT_MAX : 0));
        g2dFontSetColor(WHITE);
        g2dFontAdd();
      }
      g2dFontEnd();
    }
  }
}


void dispgSquare()
{
  static float gsquare_size = 1.4f;

  g2dBeginRects(img.gsquare);
  {
    g2dSetCoordMode(G2D_CENTER);
    g2dSetCoordXY(g2dScrW()/2,g2dScrH()/2-20);
    g2dSetScale(gsquare_size,gsquare_size);
    g2dAdd();
  }
  g2dEnd();

  gsquare_size /= 1.0004f;

  g2dFontBegin(font, text.authors);
  {
    g2dFontSetCoordMode(G2D_CENTER);
    g2dFontSetCoordXY(g2dScrW()/2,g2dScrH()-70);
    g2dFontSetColor(WHITE);
    g2dFontAdd();
  }
  g2dFontEnd();

  g2dFontBegin(font, text.website);
  {
    g2dFontSetCoordMode(G2D_CENTER);
    g2dFontSetCoordXY(g2dScrW()/2,g2dScrH()-35);
    g2dFontSetColor(WHITE);
    g2dFontAdd();
  }
  g2dFontEnd();
}


void dispBanner()
{
  g2dBeginRects(img.banner);
  {
    g2dSetTexLinear(false);
    g2dSetScaleWH(g2dScrW(),g2dScrH());
    g2dAdd();
  }
  g2dEnd();
}


void dispMenu()
{
  if (menu.state == 0)
  {
    menu.square_y_target = g2dScrH()+100.f;
    menu.logo_y_target = 150.f;
  }
  else if (menu.state == 1)
  {
    menu.square_y_target = 0.5f*g2dScrH();
    menu.logo_y_target = 0.f;
  }
  else
  {
    menu.square_y_target = -300.f;
    menu.logo_y_target = -100.f;
  }

  menu.rot += (menu.rot_target-menu.rot) * CAM_ROT_SPEED;
  menu.logo_y += (menu.logo_y_target-menu.logo_y) * CAM_POS_SPEED;
  menu.square_y += (menu.square_y_target-menu.square_y) * CAM_POS_SPEED;

  int i;
  float title_x[4], title_y[4];

  // Background shade
  g2dBeginQuads(NULL);
  {
    g2dSetColor(YELLOW);
    g2dSetAlpha(0);
    g2dSetCoordXY(0,0);
    g2dAdd();
    g2dSetCoordXY(g2dScrW(),0);
    g2dAdd();
    g2dSetAlpha(127);
    g2dSetCoordXY(g2dScrW(),g2dScrH());
    g2dAdd();
    g2dSetCoordXY(0,g2dScrH());
    g2dAdd();
  }
  g2dEnd();

  // Logo
  g2dBeginRects(img.gsquare);
  {
    g2dSetCoordMode(G2D_CENTER);
    g2dSetCoordXY(g2dScrW()/2,menu.logo_y);
    g2dAdd();
  }
  g2dEnd();

  // L/R indicator
  if (menu.state == 0)
  {
      g2dFontBegin(font, "<");
      {
        g2dFontSetCoordMode(G2D_CENTER);
        g2dFontSetCoordXY(g2dScrW()/8,g2dScrH()-70);
        g2dFontSetAlpha(ctrlPressed(KEY_LEFT) ? 255 : 127);
        g2dFontSetColor(BLACK);
        g2dFontAdd();
      }
      g2dFontEnd();
      g2dFontBegin(font, ">");
      {
        g2dFontSetCoordMode(G2D_CENTER);
        g2dFontSetCoordXY(7*g2dScrW()/8,g2dScrH()-70);
        g2dFontSetAlpha(ctrlPressed(KEY_RIGHT) ? 255 : 127);
        g2dFontSetColor(BLACK);
        g2dFontAdd();
      }
      g2dFontEnd();
  }

  g2dBeginRects(img.tileset);
  {
    // Draw Bluz
    g2dSetTexLinear(false);
    g2dSetCoordMode(G2D_CENTER);
    g2dSetCropWH(12,12);
    g2dSetScaleWH(500,500);
    g2dSetCoordXY(g2dScrW()/2,menu.square_y);
    g2dSetRotation(menu.rot);
    g2dAdd();
    
    // Get title coords
    for (i=0; i!=MENU_TITLE_NBR; i++)
    {
      g2dPush();
      g2dSetRotationRelative(i*90);
      g2dSetCoordXYRelative(0,-233);
      g2dGetCoordXYZ(&title_x[i],&title_y[i],NULL);
      g2dPop();
    }
  }
  g2dEnd();
  
  // Draw section title
  for (i=0; i!=MENU_TITLE_NBR; i++)
  {
    if (i == menu.mod_i)
    {
      g2dFontBegin(bigfont, text.menu.title[i]);
      {
        g2dFontSetCoordMode(G2D_CENTER);
        g2dFontSetCoordXY(title_x[i],title_y[i]);
        g2dFontSetRotation(menu.rot+menu.mod_i*90);
        g2dFontSetColor(WHITE);
        g2dFontAdd();
      }
      g2dFontEnd();
    }
  }
  
  // Draw section text
  if (menu.state != 0)
  {
    float text_x = title_x[menu.mod_i],
    text_y = title_y[menu.mod_i] + 70.f;
    if (menu.mod_i == 0) // Story
    {
      for (i=0; i<3; i++)
      {
        char sub_text[128];
        sprintf(sub_text,(menu.sub_i==i ? "> %s <" : "%s"),text.menu.story[i]);
        g2dFontBegin(font, sub_text);
        {
          g2dFontSetCoordMode(G2D_CENTER);
          g2dFontSetCoordXY(text_x,text_y+i*40);
          g2dFontSetRotation(menu.rot+menu.mod_i*90);
          if (menu.sub_i!=i) g2dFontSetAlpha(127);
          g2dFontSetColor(WHITE);
          g2dFontAdd();
        }
        g2dFontEnd();
      }
    }
    else if (menu.mod_i == 1) // Config
    {
      for (i=0; i<4; i++)
      {
        char sub_text[128];
        sprintf(sub_text,(menu.sub_i==i ? "%s < %s >" : "%s %s"),text.menu.config[i],text.menu.config_setting[i]);
        g2dFontBegin(font, sub_text);
        {
          g2dFontSetCoordMode(G2D_CENTER);
          g2dFontSetCoordXY(text_x,text_y+i*40);
          g2dFontSetRotation(menu.rot+menu.mod_i*90);
          if (menu.sub_i!=i) g2dFontSetAlpha(127);
          g2dFontSetColor(WHITE);
          g2dFontAdd();
        }
        g2dFontEnd();
      }
    }
    else if (menu.mod_i == 2) // Credits
    {
      g2dFontBegin(font, text.credits);
      {
        g2dFontSetCoordMode(G2D_CENTER);
        g2dFontSetCoordXY(text_x,text_y-30);
        g2dFontSetRotation(menu.rot+menu.mod_i*90);
        g2dFontSetScale(0.8f);
        g2dFontSetColor(WHITE);
        g2dFontAdd();
      }
      g2dFontEnd();
    }
  }
}

// EOF
