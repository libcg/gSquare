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

#ifndef DISP_H
#define DISP_H

#include <SDL_ttf.h>
#include "lib/glib2d.h"
#include "lib/glib2d_font.h"

#define BACK_W 30
#define BACK_H 17

#define CAM_STEP 20
#define CAM_POS_SPEED 0.06f
#define CAM_ROT_SPEED 0.18f
#define CAM_ZOOM_SPEED 0.05f
#define TIMER_SIZE_SPEED 0.1f
#define DCOUNT_MAX 30

enum fade_mode { FADE_OUT = -1, FADE_IN = 1 };
enum fade_state { FADING, FADE_DONE };

typedef struct
{
  short d[4]; // Alpha dir
  float s[4]; // Alpha speed
  float a[4]; // Alpha
} Background;

typedef struct
{
  short mode;
  float alpha;
  float speed;
  short max, min; // Limits
  float progress; // [0;1]
  g2dColor color;
} Fade;

typedef struct
{
  g2dTexture* gsquare;
  g2dTexture* banner;
  g2dTexture* back;
  g2dTexture* tileset;
  g2dTexture* end;
} Images;

typedef struct
{
  int active;
  float x_target, x;
  float y_target, y;
  float rot_target, rot;
  float zoom_target, zoom;
} Camera;

extern g2dFont *font, *bigfont, *itlfont;
extern Fade main_fade;
extern Fade ui_fade;
extern Camera cam;
extern Images img;

// Common
void setFadeMode(Fade* fade, short mode, short reset);
void setFadeColor(Fade* fade, short color);
short getFadeState(Fade* fade);
void waitFadeDone(Fade* fade);
void drawFade(Fade* fade);
void initDisp();
void dispLoop(SDL_mutex* mutex);

// Game
void setCameraRot(int rot);
void camera();
void renderShadowMask();
void drawShadowMask();
void drawLevel();

// UI
void setTimerAspect(float size, g2dColor color);
void drawUI();
void dispgSquare();
void dispBanner();
void dispMenu();
void dispEnding();

#endif
