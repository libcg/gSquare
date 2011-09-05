// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <pspkernel.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#include "disp.h"
#include "game.h"
#include "common.h"

g2dImage rendertarget;
intraFont *font, *bigfont, *seriffont;
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
    if (back.a[i] < 0.f  ) back.d[i] =  1, back.a[i] = 0.f;
    if (back.a[i] > 255.f) back.d[i] = -1, back.a[i] = 255.f;
    back.a[i] += back.d[i] * back.s[i];
  }

  g2dClear(WHITE);

  g2dBeginQuads(img.back);
    g2dSetCropWH(BACK_W-1,BACK_H-1);
    // First
    g2dSetCropXY(0,0);
    g2dSetCoordXY(0,0);
    g2dSetAlpha(back.a[0]);
    g2dAdd();
    g2dSetCoordXY(G2D_SCR_W,0);
    g2dSetAlpha(back.a[1]);
    g2dAdd();
    g2dSetCoordXY(G2D_SCR_W,G2D_SCR_H);
    g2dSetAlpha(back.a[2]);
    g2dAdd();
    g2dSetCoordXY(0,G2D_SCR_H);
    g2dSetAlpha(back.a[3]);
    g2dAdd();
    // Second
    g2dSetCropXY(BACK_W,0);
    g2dSetCoordXY(0,0);
    g2dSetAlpha(255-back.a[0]);
    g2dAdd();
    g2dSetCoordXY(G2D_SCR_W,0);
    g2dSetAlpha(255-back.a[1]);
    g2dAdd();
    g2dSetCoordXY(G2D_SCR_W,G2D_SCR_H);
    g2dSetAlpha(255-back.a[2]);
    g2dAdd();
    g2dSetCoordXY(0,G2D_SCR_H);
    g2dSetAlpha(255-back.a[3]);
    g2dAdd();
  g2dEnd();
}

// Fade

void setFadeMode(Fade* fade, short mode, short reset)
{
  fade->mode = mode;
  if (!reset) return;

  if      (mode == FADE_OUT) fade->alpha = fade->max, fade->progress = 1.f;
  else if (mode == FADE_IN ) fade->alpha = fade->min, fade->progress = 0.f;
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
  while (getFadeState(fade) != FADE_DONE) sceKernelDelayThread(1000);
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
      g2dSetScaleWH(G2D_SCR_W,G2D_SCR_H);
      g2dSetColor(fade->color);
      g2dSetAlpha(fade->alpha);
      g2dAdd();
    g2dEnd();
  }
}

// Common

g2dImage* loadImage(char path[], g2dEnum tex_mode)
{
  g2dImage* tex = g2dTexLoad(path,tex_mode);
  if (tex == NULL) throwException("Unable to load the texture (%s)\n",path);
  return tex;
}


void dispException()
{
  // BSOD ! HAHAHA
  pspDebugScreenInit();
  pspDebugScreenSetBackColor(BLUE);
  pspDebugScreenSetTextColor(WHITE);
  pspDebugScreenClear();
  pspDebugScreenPrintf(exit_err);
}


int dispThread(SceSize args, void *argp)
{
  sceIoChdir(cwd);
  initBackground();
  
  while (exit_state != EXCEPTION)
  {
    while (thread_block)
    {
      thread_disp_waiting = 1;
      sceKernelDelayThread(100);
    }
    thread_disp_waiting = 0;
  
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
      drawMovingBackground();
      camera();
      drawLevel();
      drawUI();
    }
    if (checkGameState(LEVEL_TITLE))
    {
      g2dClear(WHITE);
      intraFontSetStyle(seriffont,1.f,BLACK,0,0,INTRAFONT_ALIGN_CENTER);
      intraFontPrint(seriffont,G2D_SCR_W/2,G2D_SCR_H/2,lvl.title);
    }
    if (checkGameState(END))
    {
      g2dClear(WHITE);
      g2dBeginRects(img.end);
        g2dAdd();
      g2dEnd();
    }
    
    drawFade(&main_fade);
    g2dFlip(G2D_VSYNC);
  }
  
  if (exit_state == EXCEPTION) dispException();
  
  return 0;
}


void initDisp()
{
  // Render target, 512*512*4 (480*272, 32bit)
  rendertarget.tw = 512;
  rendertarget.th = 512;
  rendertarget.w = G2D_SCR_W;
  rendertarget.h = G2D_SCR_H;
  rendertarget.ratio = G2D_SCR_W / G2D_SCR_H;
  rendertarget.swizzled = false;
  rendertarget.can_blend = true;
  rendertarget.data = malloc(512*512*4);
  // Load images
  img.back = loadImage("graphics/back.png",G2D_SWIZZLE);
  img.tileset = loadImage("graphics/tileset.png",G2D_SWIZZLE);
  img.gsquare = loadImage("./graphics/gsquare.png",G2D_SWIZZLE);
  img.banner = loadImage("./graphics/genesis.png",G2D_SWIZZLE);
  // Init libraries
  intraFontInit();
  font = intraFontLoad("flash0:/font/ltn8.pgf",INTRAFONT_CACHE_MED);
  bigfont = intraFontLoad("flash0:/font/ltn0.pgf",INTRAFONT_CACHE_MED);
  seriffont = intraFontLoad("flash0:/font/ltn1.pgf",INTRAFONT_CACHE_MED);
  intraFontSetEncoding(font,INTRAFONT_STRING_UTF8);
  intraFontSetEncoding(bigfont,INTRAFONT_STRING_UTF8);
  intraFontSetEncoding(seriffont,INTRAFONT_STRING_UTF8);
  // Start display thread
  SceUID thid = sceKernelCreateThread("disp_thread",dispThread,0x10,0x1000,
                                      THREAD_ATTR_USER | THREAD_ATTR_VFPU,0);
  if (thid < 0)
  {
    throwException("Can't create the display thread\n");
  }
  if (sceKernelStartThread(thid,0,0))
  {
    throwException("Can't start the display thread\n");
  }
}

// EOF
