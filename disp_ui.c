// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <stdio.h>
#include "game.h"
#include "disp.h"
#include "controls.h"
#include "common.h"
#include "level.h"
#include "audio.h"
#include "language.h"

#include "lib/glib2d.h"

Fade ui_fade = {FADE_OUT,0.f,3.5f,255,0,0.f,BLACK};
g2dColor timer_back_color = WHITE;
float timer_size = 1.f, gsquare_size = 1.f;
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

  if (getGameState() == INGAME)
  {
    ui_fade.mode = FADE_OUT;
    cam.zoom_target = 1.6f;
    // Timer TODO
    // L/R indicator TODO
    // Flying text TODO
  }
  else if (getGameState() == WIN)
  {
    ui_fade.color = WHITE;
    ui_fade.max = 255;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 3.f;
    // TODO title
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      // TODO next level
    }
  }
  else if (getGameState() == TIME_OVER)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 255;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 1.f;
    // TODO title
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      // TODO respawn
    }
  }
  else if (getGameState() == OUT_OF_BOUNDS)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 127;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 1.f;
    // TODO title
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      // TODO respawn
    }
  }
  else if (getGameState() == DEATH)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 127;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 1.f;
    // TODO title
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      // TODO respawn
    }
  }
  else if (getGameState() == PAUSE)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 127;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 0.85f;
    // TODO title
    
    int i;
    for (i=0; i!=PAUSE_CHOICE_NBR; i++)
    {
      // TODO menu
      if (pause.i == i && dcount < DCOUNT_MAX * 5 / 6)
      {
        // TODO menu selector
      }
    }
  }
}


void dispgSquare()
{
  gsquare_size /= 1.0002f;
  g2dBeginRects(img.gsquare);
  {
    g2dSetCoordMode(G2D_CENTER);
    g2dSetCoordXY(G2D_SCR_W/2,G2D_SCR_H/2-20);
    g2dSetScale(gsquare_size,gsquare_size);
    g2dAdd();
  }
  g2dEnd();
  
  // TODO authors, website
}


void dispBanner()
{
  g2dBeginRects(img.banner);
  {
    g2dSetTexLinear(false);
    g2dSetScaleWH(G2D_SCR_W,G2D_SCR_H);
    g2dAdd();
  }
  g2dEnd();
}


void dispMenu()
{
  if (menu.state == 0)
  {
    menu.square_y_target = G2D_SCR_H+100.f;
    menu.logo_y_target = 150.f;
  }
  else if (menu.state == 1)
  {
    menu.square_y_target = 320.f;
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
    g2dSetCoordXY(G2D_SCR_W,0);
    g2dAdd();
    g2dSetAlpha(127);
    g2dSetCoordXY(G2D_SCR_W,G2D_SCR_H);
    g2dAdd();
    g2dSetCoordXY(0,G2D_SCR_H);
    g2dAdd();
  }
  g2dEnd();

  // Logo
  g2dBeginRects(img.gsquare);
  {
    g2dSetCoordMode(G2D_CENTER);
    g2dSetCoordXY(G2D_SCR_W/2,menu.logo_y);
    g2dAdd();
  }
  g2dEnd();

  // L/R indicator
  if (menu.state == 0)
  {
    // TODO
  }

  g2dBeginRects(img.tileset);
  {
    // Draw Bluz
    g2dSetTexLinear(false);
    g2dSetCoordMode(G2D_CENTER);
    g2dSetCropWH(12,12);
    g2dSetScaleWH(500,500);
    g2dSetCoordXY(G2D_SCR_W/2,menu.square_y);
    g2dSetRotation(menu.rot);
    g2dAdd();
    
    // Get title coords
    for (i=0; i!=MENU_TITLE_NBR; i++)
    {
      g2dPush();
      g2dSetRotationRelative(i*90);
      g2dSetCoordXYRelative(0,-155);
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
      // TODO
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
        // TODO
      }
    }
    else if (menu.mod_i == 1) // Config
    {
      for (i=0; i<3; i++)
      {
        // TODO
      }
    }
    else if (menu.mod_i == 2) // Credits
    {
      // TODO
    }
  }
}

// EOF
