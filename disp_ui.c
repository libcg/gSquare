// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <pspkernel.h>
#include <stdio.h>
#include "game.h"
#include "disp.h"
#include "controls.h"
#include "common.h"
#include "level.h"
#include "audio.h"
#include "language.h"

#include "lib/glib2d.h"
#include "lib/pspaalib.h"
#include "lib/intraFont.h"

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
    // Timer
    intraFontSetStyle(bigfont,timer_size,BLACK,timer_back_color,0.f,
                      INTRAFONT_ALIGN_CENTER);
    intraFontPrintf(bigfont,G2D_SCR_W/2,20,"%.2d:%.2d",
                    game.time_elapsed/60,game.time_elapsed%60);
    // L/R indicator
    short l = buttonPressed(PSP_CTRL_LTRIGGER) && !game.g_lock,
          r = buttonPressed(PSP_CTRL_RTRIGGER) && !game.g_lock;
    intraFontSetStyle(font,1.1f,(game.g_lock ? GRAY : BLACK),
                      (l ? RED : 0),0.f,INTRAFONT_ALIGN_CENTER);
    intraFontPrint(font,15,15,"<L");
    intraFontSetStyle(font,1.1f,(game.g_lock ? GRAY : BLACK),
                      (r ? RED : 0),0.f,INTRAFONT_ALIGN_CENTER);
    intraFontPrint(font,G2D_SCR_W-15,15,"R>");
    // Flying text     
    if (game.flying_text != NULL)
    {
      intraFontSetStyle(font,0.9f,BLACK,AZURE,0.f,INTRAFONT_ALIGN_CENTER);
      intraFontPrintf(font,G2D_SCR_W/2,260,"%s",game.flying_text);
    }
  }
  else if (getGameState() == WIN)
  {
    ui_fade.color = WHITE;
    ui_fade.max = 255;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 3.f;
    intraFontSetStyle(bigfont,0.9f,BLACK,0,0.f,INTRAFONT_ALIGN_CENTER);
    intraFontPrint(bigfont,G2D_SCR_W/2,G2D_SCR_H/2,text.game.win);
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      intraFontSetStyle(font,1.f,G2D_MODULATE(BLACK,255,255*dcount/DCOUNT_MAX),0,
                        0.f,INTRAFONT_ALIGN_RIGHT);
      intraFontPrint(font,G2D_SCR_W-5,G2D_SCR_H-5,text.game.next_level);
    }
  }
  else if (getGameState() == TIME_OVER)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 255;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 1.f;
    intraFontSetStyle(bigfont,0.9f,WHITE,0,0.f,INTRAFONT_ALIGN_CENTER);
    intraFontPrint(bigfont,G2D_SCR_W/2,G2D_SCR_H/2,text.game.time_over);
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      intraFontSetStyle(font,1.f,G2D_MODULATE(WHITE,255,255*dcount/DCOUNT_MAX),0,
                        0.f,INTRAFONT_ALIGN_RIGHT);
      intraFontPrint(font,G2D_SCR_W-5,G2D_SCR_H-5,text.game.respawn);
    }
  }
  else if (getGameState() == OUT_OF_BOUNDS)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 127;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 1.f;
    intraFontSetStyle(bigfont,0.9f,WHITE,BLACK,0.f,INTRAFONT_ALIGN_CENTER);
    intraFontPrint(bigfont,G2D_SCR_W/2,G2D_SCR_H/2,text.game.out_bounds);
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      intraFontSetStyle(font,1.f,G2D_MODULATE(WHITE,255,255*dcount/DCOUNT_MAX),0,
                        0.f,INTRAFONT_ALIGN_RIGHT);
      intraFontPrint(font,G2D_SCR_W-5,G2D_SCR_H-5,text.game.respawn);
    }
  }
  else if (getGameState() == DEATH)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 127;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 1.f;
    intraFontSetStyle(bigfont,0.9f,WHITE,BLACK,0.f,INTRAFONT_ALIGN_CENTER);
    intraFontPrint(bigfont,G2D_SCR_W/2,G2D_SCR_H/2,text.game.death);
    if (dcount < DCOUNT_MAX * 5 / 6)
    {
      intraFontSetStyle(font,1.f,G2D_MODULATE(WHITE,255,255*dcount/DCOUNT_MAX),0,
                        0.f,INTRAFONT_ALIGN_RIGHT);
      intraFontPrint(font,G2D_SCR_W-5,G2D_SCR_H-5,text.game.respawn);
    }
  }
  else if (getGameState() == PAUSE)
  {
    ui_fade.color = BLACK;
    ui_fade.max = 127;
    ui_fade.mode = FADE_IN;
    cam.zoom_target = 0.85f;
    intraFontSetStyle(bigfont,0.9f,WHITE,BLACK,0.f,INTRAFONT_ALIGN_CENTER);
    intraFontPrint(bigfont,G2D_SCR_W/2,G2D_SCR_H/2,text.game.pause);
    
    int i;
    for (i=0; i!=PAUSE_CHOICE_NBR; i++)
    {
      intraFontSetStyle(font,1.f,WHITE,(pause.i == i ? 0 : BLACK),
                        0.f,INTRAFONT_ALIGN_RIGHT);
      intraFontPrintf(font,G2D_SCR_W-15,G2D_SCR_H-5-15*i,
                      text.game.pause_choice[i]);
      if (pause.i == i && dcount < DCOUNT_MAX * 5 / 6)
      {
        intraFontSetStyle(font,1.f,G2D_MODULATE(WHITE,255,255*dcount/DCOUNT_MAX),
                          0,0.f,INTRAFONT_ALIGN_RIGHT);
        intraFontPrintf(font,G2D_SCR_W-5,G2D_SCR_H-5-15*i,"<");
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
  
  intraFontSetStyle(font,1.f,WHITE,0,0.f,INTRAFONT_ALIGN_CENTER);
  intraFontPrint(font,480/2,240,text.authors);
  intraFontPrint(font,480/2,262,text.website);
}


void dispBanner()
{
  g2dBeginRects(img.banner);
  {
    g2dAdd();
  }
  g2dEnd();
}


void dispMenu()
{
  if (menu.state == 0)
  {
    menu.square_y_target = 370.f;
    menu.logo_y_target = 70.f; 
  }
  else if (menu.state == 1)
  {
    menu.square_y_target = 190.f;
    menu.logo_y_target = -30.f; 
  }
  else
  {
    menu.square_y_target = -250.f;
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
    g2dSetScale(0.8f,0.8f);
    g2dAdd();
  }
  g2dEnd();

  // L/R indicator
  if (menu.state == 0)
  {
    intraFontSetStyle(bigfont,1.f,BLACK,
                      (buttonPressed(PSP_CTRL_LTRIGGER) ? RED : 0),0.f,
                      INTRAFONT_ALIGN_CENTER);
    intraFontPrint(bigfont,25,G2D_SCR_H-25,"<L");
    intraFontSetStyle(bigfont,1.f,BLACK,
                      (buttonPressed(PSP_CTRL_RTRIGGER) ? RED : 0),0.f,
                      INTRAFONT_ALIGN_CENTER);
    intraFontPrint(bigfont,G2D_SCR_W-25,G2D_SCR_H-25,"R>");
  }

  g2dBeginRects(img.tileset);
  {
    // Draw Bluz
    g2dSetTexLinear(false);
    g2dSetCoordMode(G2D_CENTER);
    g2dSetCropWH(12,12);
    g2dSetScaleWH(350,350);
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
      intraFontSetStyle(bigfont,1.f,WHITE,BLACK,menu.rot+menu.mod_i*90,
                        INTRAFONT_ALIGN_CENTER);
      intraFontPrint(bigfont,title_x[i],title_y[i],text.menu.title[i]);
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
        intraFontSetStyle(font,1.f,WHITE,(i == menu.sub_i ? 0 : BLACK),
                          menu.rot+menu.mod_i*90,INTRAFONT_ALIGN_CENTER);
        intraFontPrintf(font,text_x,text_y+i*30,
                        (i==menu.sub_i ? "> %s <" : "%s"),text.menu.story[i]);
      }
    }
    else if (menu.mod_i == 1) // Config
    {
      for (i=0; i<3; i++)
      {
        intraFontSetStyle(font,1.f,WHITE,(i == menu.sub_i ? 0 : BLACK),
                          menu.rot+menu.mod_i*90,INTRAFONT_ALIGN_CENTER);
        intraFontPrintf(font,text_x,text_y+i*30,
                        (i==menu.sub_i ? "< %s %s >" : "%s %s"),
                        text.menu.config[i],text.menu.config_setting[i]);
      }
    }
    else if (menu.mod_i == 2) // Credits
    {
      intraFontSetStyle(font,1.f,WHITE,0,
                        menu.rot+menu.mod_i*90,INTRAFONT_ALIGN_CENTER);
      intraFontPrint(font,text_x,text_y-40.f,text.credits);
    }
  }
}

// EOF
