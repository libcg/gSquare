// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef DISP_H
#define DISP_H

#include "lib/glib2d.h"
#include "lib/intraFont.h"

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
  g2dImage* gsquare;
  g2dImage* banner;
  g2dImage* back;
  g2dImage* tileset;
  g2dImage* end;
} Images;

typedef struct
{
  int active;
  float x_target, x;
  float y_target, y;
  float rot_target, rot;
  float zoom_target, zoom;
} Camera;

extern g2dImage rendertarget;
extern intraFont *font, *bigfont, *seriffont;
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

#endif
