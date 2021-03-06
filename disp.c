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

#include <stdlib.h>
#include <time.h>
#include <SDL_timer.h>
#include <SDL_image.h>

#include "disp.h"
#include "game.h"
#include "common.h"
#include "config.h"

g2dFont *font, *bigfont, *itlfont;
Images img;
Fade main_fade = {FADE_OUT,255.f,3.5f,255,0,0.f,BLACK};
Background back;

// Background

void initBackground()
{
  srand(time(NULL));
  int i;
  for (i=0; i!=4; i++)
  {
    back.d[i] = (rand()%2  ) * 2 - 1; // dir: -1 or 1
    back.s[i] = (rand()%100) / 100.f; // speed: [0;1]
    back.a[i] = (rand()%255);         // alpha: [0;255]
  }
}


void drawMovingBackground()
{
  int i;
  for (i=0; i!=4; i++)
  {
    if (back.a[i] < 0.f  )
    {
      back.d[i] =  1;
      back.a[i] = 0.f;
    }
    if (back.a[i] > 255.f)
    {
      back.d[i] = -1;
      back.a[i] = 255.f;
    }
    back.a[i] += back.d[i] * back.s[i];
  }

  g2dClear(WHITE);

  g2dBeginQuads(img.back);
  {
    g2dSetCropWH(BACK_W-1,BACK_H-1);
    // First
    g2dSetCropXY(0,0);
    g2dSetCoordXY(0,0);
    g2dSetAlpha(back.a[0]);
    g2dAdd();
    g2dSetCoordXY(g2dScrW(),0);
    g2dSetAlpha(back.a[1]);
    g2dAdd();
    g2dSetCoordXY(g2dScrW(),g2dScrH());
    g2dSetAlpha(back.a[2]);
    g2dAdd();
    g2dSetCoordXY(0,g2dScrH());
    g2dSetAlpha(back.a[3]);
    g2dAdd();
    // Second
    g2dSetCropXY(BACK_W,0);
    g2dSetCoordXY(0,0);
    g2dSetAlpha(255-back.a[0]);
    g2dAdd();
    g2dSetCoordXY(g2dScrW(),0);
    g2dSetAlpha(255-back.a[1]);
    g2dAdd();
    g2dSetCoordXY(g2dScrW(),g2dScrH());
    g2dSetAlpha(255-back.a[2]);
    g2dAdd();
    g2dSetCoordXY(0,g2dScrH());
    g2dSetAlpha(255-back.a[3]);
    g2dAdd();
  }
  g2dEnd();
}

// Fade

void setFadeMode(Fade* fade, short mode, short reset)
{
  fade->mode = mode;
  if (!reset)
  {
    return;
  }

  if (mode == FADE_OUT)
  {
    fade->alpha = fade->max;
    fade->progress = 1.f;
  }
  else if (mode == FADE_IN )
  {
    fade->alpha = fade->min;
    fade->progress = 0.f;
  }
}


void setFadeColor(Fade* fade, short color)
{
  fade->color = color;
}


short getFadeState(Fade* fade)
{
  return ((fade->mode == FADE_IN  && fade->alpha == fade->max) ||
          (fade->mode == FADE_OUT && fade->alpha == fade->min))
         ? FADE_DONE : FADING;
}


void waitFadeDone(Fade* fade)
{
  while (getFadeState(fade) != FADE_DONE)
  {
    SDL_SemPost(render_sem);
    SDL_Delay(1);
  }
}


void drawFade(Fade* fade)
{
  fade->alpha += fade->mode * fade->speed;
  if (fade->alpha > fade->max) fade->alpha = fade->max;
  else if (fade->alpha < fade->min) fade->alpha = fade->min;
  fade->progress = (float)fade->alpha / (fade->max - fade->min);

  if (fade->alpha != 0)
  {
    g2dBeginRects(NULL);
    {
      g2dSetScaleWH(g2dScrW(),g2dScrH());
      g2dSetColor(fade->color);
      g2dSetAlpha(fade->alpha);
      g2dAdd();
    }
    g2dEnd();
  }
}

// Common

static void processEvents()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      exit_state = 1;
      break;
    }
  }
}


static g2dTexture* loadImage(char path[], g2dTex_Mode mode)
{
  g2dTexture* tex = g2dTexLoad(path,mode);
  if (tex == NULL) throwException(IMG_GetError());
  return tex;
}


static void loadTextures()
{
  img.back = loadImage("graphics/back.png",0);
  img.tileset = loadImage("graphics/tileset.png",0);
  img.gsquare = loadImage("graphics/gsquare.png",0);
  img.banner = loadImage("graphics/genesis.png",0);
  img.end = loadImage("./graphics/end.png",0);
}


static void freeTextures()
{
  g2dTexFree(&img.back);
  g2dTexFree(&img.tileset);
  g2dTexFree(&img.gsquare);
  g2dTexFree(&img.banner);
  g2dTexFree(&img.end);
}


static void manageScreenMode()
{
  Config *cfg = configGet();
  static bool fs = true;

  if (fs != cfg->fullscreen)
  {
    // This has to be done in the disp thread.
    // Also, GL textures are lost during mode change so reload them.
    freeTextures();
    g2dFontInvalidate();
    g2dSetMode(cfg->fullscreen);
    loadTextures();
  }

  fs = cfg->fullscreen;
}


void dispLoop()
{
  while (exit_state != EXCEPTION)
  {
    processEvents();
    manageScreenMode();

    if (exit_state)
    {
      setFadeMode(&main_fade,FADE_IN,0);
      if (getFadeState(&main_fade) == FADE_DONE) break;
    }
 
    if (checkGameState(GSQUARE))
    {
      g2dClear(BLACK);
      dispgSquare();
    }
    if (checkGameState(BANNER))
    {
      g2dClear(BLACK);
      dispBanner();
    }
    if (checkGameState(MENU))
    {
      drawMovingBackground();
      dispMenu();
    }
    if (checkGameState(INGAME))
    {
      SDL_SemWait(render_sem);

      drawMovingBackground();
      camera();
      drawLevel();
      drawUI();

      SDL_SemPost(logic_sem);
    }
    if (checkGameState(LEVEL_TITLE))
    {
      g2dClear(WHITE);
      g2dFontBegin(itlfont, lvl.title);
      {
        g2dFontSetCoordMode(G2D_CENTER);
        g2dFontSetCoordXY(g2dScrW()/2,g2dScrH()/2);
        g2dFontSetColor(BLACK);
        g2dFontAdd();
      }
      g2dFontEnd();
    }
    if (checkGameState(END))
    {
      g2dClear(BLACK);
      dispEnding();
    }
    
    drawFade(&main_fade);
    g2dFlip(G2D_VSYNC);
  }
}


void initDisp()
{
  loadTextures();

  g2dFontInit();
  font = g2dFontLoad("fonts/Cantarell-Bold.ttf",24);
  bigfont = g2dFontLoad("fonts/Cantarell-Bold.ttf",36);
  itlfont = g2dFontLoad("fonts/Cantarell-Oblique.ttf",36);
  if (!font || !bigfont || !itlfont) throwException("Couldn't open font\n");

  initBackground();
}

// EOF
