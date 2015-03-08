/*
 * gLib2D by Geecko - A simple, fast, light-weight 2D graphics library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * If you find any bug, contact me at <geecko.dev@free.fr>
 */

#include "glib2d.h"

#if defined(__MACOSX__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <SDL_video.h>
#include <SDL_image.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#ifdef USE_PNG
#include <png.h>
#endif

#ifdef USE_JPEG
#include <jpeglib.h>
#include <jerror.h>
#endif

#define PSP_LINE_SIZE       (512)
#define PIXEL_SIZE          (4)
#define FRAMEBUFFER_SIZE    (PSP_LINE_SIZE*G2D_SCR_H*PIXEL_SIZE)
#define MALLOC_STEP         (128)
#define TRANSFORM_STACK_MAX (64)
#define SLICE_WIDTH         (64)
#define M_180_PI            (57.29578f)
#define M_PI_180            (0.017453292f)

#define DEFAULT_SIZE       (10)
#define DEFAULT_COORD_MODE (G2D_UP_LEFT)
#define DEFAULT_X          (0.f)
#define DEFAULT_Y          (0.f)
#define DEFAULT_Z          (0.f)
#define DEFAULT_COLOR      (WHITE)
#define DEFAULT_ALPHA      (0xFF)

#define CURRENT_OBJ obj_list[obj_list_size-1]
#define CURRENT_TRANSFORM transform_stack[transform_stack_size-1]
#define I_OBJ obj_list[i]

typedef enum
{
  RECTS, LINES, QUADS, POINTS
} Obj_Type;

typedef struct
{
  float x, y, z;
  float rot, rot_sin, rot_cos;
  float scale_w, scale_h;
} Transform;

typedef struct
{
  float x, y, z;
  float rot_x, rot_y; // Rotation center
  float rot, rot_sin, rot_cos;
  int crop_x, crop_y;
  int crop_w, crop_h;
  float scale_w, scale_h;
  g2dColor color;
  g2dAlpha alpha;
} Object;


// * Main vars *
static SDL_Window *window = NULL;
static SDL_GLContext glctx;
static bool init = false, start = false, zclear = true, scissor = false;
static Transform transform_stack[TRANSFORM_STACK_MAX];
static int transform_stack_size;
static float global_scale = 1.f;
// * Object vars *
static Object *obj_list = NULL, obj;
static Obj_Type obj_type;
static int obj_list_size;
static bool obj_begin = false, obj_line_strip;
static bool obj_use_z, obj_use_blend, obj_use_rot,
            obj_use_tex_linear, obj_use_tex_repeat, obj_use_int;
static g2dCoord_Mode obj_coord_mode;
static int obj_colors_count;
static g2dImage* obj_tex;

// * Internal functions *


void _g2dInit()
{
  // Setup SDL
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow(
    "gLib2D - gSquare",
    SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
    G2D_SCR_W,G2D_SCR_H,
    SDL_WINDOW_OPENGL
  );

  glctx = SDL_GL_CreateContext(window);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
  SDL_GL_SetSwapInterval(1);

  // Setup OpenGL
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,G2D_SCR_W,G2D_SCR_H,0,0,1);
  glMatrixMode(GL_MODELVIEW);

  g2dResetScissor();
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_BLEND);
  glEnable(GL_SCISSOR_TEST);
  glDepthFunc(GL_GEQUAL);
  glDepthRange(0,65535);
  glClearDepth(0);

  init = true;
}


void _g2dStart()
{
  if (!init) _g2dInit();

  start = true;
}


void _g2dSetVertex(int i, int vx, int vy)
{
  // Texture
  if (obj_tex != NULL)
  {
    glTexCoord2f((float)(I_OBJ.crop_x + vx * I_OBJ.crop_w) / obj_tex->w,
                 (float)(I_OBJ.crop_y + vy * I_OBJ.crop_h) / obj_tex->h);
  }

  // Color
  glColor4f(G2D_GET_R(I_OBJ.color)/255.f,
            G2D_GET_G(I_OBJ.color)/255.f,
            G2D_GET_B(I_OBJ.color)/255.f,
            G2D_GET_A(I_OBJ.color)/255.f);

  // Coord
  float x = I_OBJ.x + (obj_type == RECTS ? vx * I_OBJ.scale_w : 0.f);
  float y = I_OBJ.y + (obj_type == RECTS ? vy * I_OBJ.scale_h : 0.f);
  float z = I_OBJ.z;

  // Then apply the rotation
  if (obj_use_rot && obj_type == RECTS)
  {
    float tx = x-I_OBJ.rot_x, ty = y-I_OBJ.rot_y;
    x = I_OBJ.rot_x - I_OBJ.rot_sin*ty + I_OBJ.rot_cos*tx,
    y = I_OBJ.rot_y + I_OBJ.rot_cos*ty + I_OBJ.rot_sin*tx;
  }

  if (obj_use_int)
  {
    x = floorf(x);
    y = floorf(y);
  }

  glVertex3f(x,y,z);
}

// * Main functions *

void g2dClear(g2dColor color)
{
  if (!start) _g2dStart();

  glClearColor(G2D_GET_R(color)/255.f,G2D_GET_G(color)/255.f,
               G2D_GET_B(color)/255.f,G2D_GET_A(color)/255.f);
  glClear(GL_COLOR_BUFFER_BIT | (zclear ? GL_DEPTH_BUFFER_BIT : 0));
  zclear = false;
}


void g2dClearZ()
{
  if (!start) _g2dStart();

  glClear(GL_DEPTH_BUFFER_BIT);
  zclear = true;
}


void _g2dBeginCommon()
{
  if (!start) _g2dStart();

  obj_list_size = 0;
  obj_list = (Object*)realloc(obj_list,MALLOC_STEP * sizeof(Object));

  obj_use_z = false;
  obj_use_blend = false;
  obj_use_rot = false;
  obj_use_int = false;
  obj_colors_count = 0;
  g2dReset();

  obj_begin = true;
}


void g2dBeginRects(g2dImage* tex)
{
  if (obj_begin) return;

  obj_type = RECTS;
  obj_tex = tex;
  _g2dBeginCommon();
}


void g2dBeginLines(g2dLine_Mode mode)
{
  if (obj_begin) return;

  obj_type = LINES;
  obj_tex = NULL;
  obj_line_strip = (mode & G2D_STRIP);
  _g2dBeginCommon();
}


void g2dBeginQuads(g2dImage* tex)
{
  if (obj_begin) return;

  obj_type = QUADS;
  obj_tex = tex;
  _g2dBeginCommon();
}


void g2dBeginPoints()
{
  if (obj_begin) return;

  obj_type = POINTS;
  obj_tex = NULL;
  _g2dBeginCommon();
}


void _g2dEndRects()
{
  glBegin(GL_TRIANGLES);

  // Add each object
  int i;
  for (i=0; i<obj_list_size; i+=1)
  {
    _g2dSetVertex(i,0,0);
    _g2dSetVertex(i,1,0);
    _g2dSetVertex(i,0,1);
    _g2dSetVertex(i,0,1);
    _g2dSetVertex(i,1,0);
    _g2dSetVertex(i,1,1);
  }

  // Then put it in the display list.
  glEnd();
}


void _g2dEndLines()
{
  glBegin(obj_line_strip ? GL_LINE_STRIP : GL_LINES);

  // Add each object
  int i;
  if (obj_line_strip)
  {
    _g2dSetVertex(0,0,0);
    for (i=1; i<obj_list_size; i+=1)
    {
      _g2dSetVertex(i,0,0);
    }
  }
  else
  {
    for (i=0; i+1<obj_list_size; i+=2)
    {
      _g2dSetVertex(i  ,0,0);
      _g2dSetVertex(i+1,0,0);
    }
  }

  // Then put it in the display list.
  glEnd();
}


void _g2dEndQuads()
{
  glBegin(GL_TRIANGLES);

  // Add each object
  int i;
  for (i=0; i+3<obj_list_size; i+=4)
  {
    _g2dSetVertex(i  ,0,0);
    _g2dSetVertex(i+1,1,0);
    _g2dSetVertex(i+3,0,1);
    _g2dSetVertex(i+3,0,1);
    _g2dSetVertex(i+1,1,0);
    _g2dSetVertex(i+2,1,1);
  }

  // Then put it in the display list.
  glEnd();
}


void _g2dEndPoints()
{
  glBegin(GL_POINTS);

  // Add each object
  int i;
  for (i=0; i<obj_list_size; i+=1)
  {
    _g2dSetVertex(i,0,0);
  }

  // Then put it in the display list.
  glEnd();
}


void g2dEnd()
{
  if (!obj_begin || obj_list_size <= 0)
  {
    obj_begin = false;
    return;
  }

  // Manage extensions
  if (obj_use_z)          glEnable(GL_DEPTH_TEST);
  else                    glDisable(GL_DEPTH_TEST);
  if (obj_use_blend)      glEnable(GL_BLEND);
  else                    glDisable(GL_BLEND);
  if (obj_tex == NULL)    glDisable(GL_TEXTURE_2D);
  else
  {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,obj_tex->id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,
                    obj_use_tex_linear ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,
                    obj_use_tex_linear ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  }

  switch (obj_type)
  {
    case RECTS:  _g2dEndRects();  break;
    case LINES:  _g2dEndLines();  break;
    case QUADS:  _g2dEndQuads();  break;
    case POINTS: _g2dEndPoints(); break;
  }

  glColor3f(1.f,1.f,1.f);
  glEnable(GL_BLEND);

  obj_begin = false;
  if (obj_use_z) zclear = true;
}


void g2dReset()
{
  g2dResetCoord();
  g2dResetScale();
  g2dResetColor();
  g2dResetAlpha();
  g2dResetRotation();
  g2dResetCrop();
  g2dResetTex();
}


void g2dFlip(g2dFlip_Mode mode)
{
  if (scissor) g2dResetScissor();

  glFinish();
  SDL_GL_SwapWindow(window);

  start = false;
}


void g2dAdd()
{
  if (!obj_begin) return;
  if (obj.scale_w == 0 || obj.scale_h == 0) return;

  if (!(obj_list_size % MALLOC_STEP))
  {
    obj_list = realloc(obj_list,(obj_list_size+MALLOC_STEP) * sizeof(Object));
  }

  obj_list_size++;
  obj.rot_x = obj.x;
  obj.rot_y = obj.y;
  CURRENT_OBJ = obj;

  // Coord mode stuff
  CURRENT_OBJ.x -= (obj_coord_mode == G2D_UP_RIGHT ||
                    obj_coord_mode == G2D_DOWN_RIGHT ?
                    CURRENT_OBJ.scale_w :
                   (obj_coord_mode == G2D_CENTER ?
                    CURRENT_OBJ.scale_w/2 : 0));
  CURRENT_OBJ.y -= (obj_coord_mode == G2D_DOWN_LEFT ||
                    obj_coord_mode == G2D_DOWN_RIGHT ?
                    CURRENT_OBJ.scale_h :
                   (obj_coord_mode == G2D_CENTER ?
                    CURRENT_OBJ.scale_h/2 : 0));

  // Alpha stuff
  CURRENT_OBJ.color = G2D_MODULATE(CURRENT_OBJ.color,255,obj.alpha);
}


void g2dPush()
{
  if (transform_stack_size >= TRANSFORM_STACK_MAX) return;
  transform_stack_size++;
  CURRENT_TRANSFORM.x = obj.x;
  CURRENT_TRANSFORM.y = obj.y;
  CURRENT_TRANSFORM.z = obj.z;
  CURRENT_TRANSFORM.rot = obj.rot;
  CURRENT_TRANSFORM.rot_sin = obj.rot_sin;
  CURRENT_TRANSFORM.rot_cos = obj.rot_cos;
  CURRENT_TRANSFORM.scale_w = obj.scale_w;
  CURRENT_TRANSFORM.scale_h = obj.scale_h;
}


void g2dPop()
{
  if (transform_stack_size <= 0) return;
  obj.x = CURRENT_TRANSFORM.x;
  obj.y = CURRENT_TRANSFORM.y;
  obj.z = CURRENT_TRANSFORM.z;
  obj.rot = CURRENT_TRANSFORM.rot;
  obj.rot_sin = CURRENT_TRANSFORM.rot_sin;
  obj.rot_cos = CURRENT_TRANSFORM.rot_cos;
  obj.scale_w = CURRENT_TRANSFORM.scale_w;
  obj.scale_h = CURRENT_TRANSFORM.scale_h;
  if (obj.rot != 0.f) obj_use_rot = true;
  if (obj.z != 0.f) obj_use_z = true;
  transform_stack_size--;
}

// * Coord functions *

void g2dResetCoord()
{
  obj_coord_mode = DEFAULT_COORD_MODE;
  obj.x = DEFAULT_X;
  obj.y = DEFAULT_Y;
  obj.z = DEFAULT_Z;
}


void g2dSetCoordMode(g2dCoord_Mode mode)
{
  if (mode > G2D_CENTER) return;
  obj_coord_mode = mode;
}


void g2dGetCoordXYZ(float* x, float* y, float* z)
{
  if (x != NULL) *x = obj.x;
  if (y != NULL) *y = obj.y;
  if (z != NULL) *z = obj.z;
}


void g2dSetCoordXY(float x, float y)
{
  obj.x = x * global_scale;
  obj.y = y * global_scale;
  obj.z = 0.f;
}


void g2dSetCoordXYZ(float x, float y, float z)
{
  obj.x = x * global_scale;
  obj.y = y * global_scale;
  obj.z = z * global_scale;
  if (z != 0.f) obj_use_z = true;
}


void g2dSetCoordXYRelative(float x, float y)
{
  float inc_x = x, inc_y = y;
  if (obj.rot_cos != 1.f)
  {
    inc_x = -obj.rot_sin*y + obj.rot_cos*x;
    inc_y =  obj.rot_cos*y + obj.rot_sin*x;
  }
  obj.x += inc_x * global_scale;
  obj.y += inc_y * global_scale;
}


void g2dSetCoordXYZRelative(float x, float y, float z)
{
  g2dSetCoordXYRelative(x,y);
  obj.z += z * global_scale;
  if (z != 0.f) obj_use_z = true;
}


void g2dSetCoordInteger(bool use)
{
  obj_use_int = use;
}

// * Scale functions *

void g2dResetGlobalScale()
{
  global_scale = 1.f;
}


void g2dResetScale()
{
  if (obj_tex == NULL)
  {
    obj.scale_w = DEFAULT_SIZE;
    obj.scale_h = DEFAULT_SIZE;
  }
  else
  {
    obj.scale_w = obj_tex->w;
    obj.scale_h = obj_tex->h;
  }

  obj.scale_w *= global_scale;
  obj.scale_h *= global_scale;
}


void g2dGetGlobalScale(float* scale)
{
  if (scale != NULL) *scale = global_scale;
}


void g2dGetScaleWH(float* w, float* h)
{
  if (w != NULL) *w = obj.scale_w;
  if (h != NULL) *h = obj.scale_h;
}


void g2dSetGlobalScale(float scale)
{
  global_scale = scale;
}


void g2dSetScale(float w, float h)
{
  g2dResetScale();
  g2dSetScaleRelative(w,h);
}


void g2dSetScaleWH(float w, float h)
{
  obj.scale_w = w * global_scale;
  obj.scale_h = h * global_scale;
  // A trick to prevent an unexpected behavior when mirroring with GU_SPRITES.
  if (obj.scale_w < 0 || obj.scale_h < 0) obj_use_rot = true;
}


void g2dSetScaleRelative(float w, float h)
{
  obj.scale_w *= w;
  obj.scale_h *= h;

  if (obj.scale_w < 0 || obj.scale_h < 0) obj_use_rot = true;
}


void g2dSetScaleWHRelative(float w, float h)
{
  obj.scale_w += w * global_scale;
  obj.scale_h += h * global_scale;

  if (obj.scale_w < 0 || obj.scale_h < 0) obj_use_rot = true;
}

// * Color functions *

void g2dResetColor()
{
  obj.color = DEFAULT_COLOR;
}


void g2dResetAlpha()
{
  obj.alpha = DEFAULT_ALPHA;
}


void g2dGetAlpha(g2dAlpha* alpha)
{
  if (alpha != NULL) *alpha = obj.alpha;
}


void g2dSetColor(g2dColor color)
{
  obj.color = color;
  if (G2D_GET_A(obj.color) < 255) obj_use_blend = true;
}


void g2dSetAlpha(g2dAlpha alpha)
{
  if (alpha < 0) alpha = 0;
  if (alpha > 255) alpha = 255;
  obj.alpha = alpha;
  if (obj.alpha < 255) obj_use_blend = true;
}


void g2dSetAlphaRelative(int alpha)
{
  g2dSetAlpha(obj.alpha + alpha);
}

// * Rotations functions *

void g2dResetRotation()
{
  obj.rot = 0.f;
  obj.rot_sin = 0.f;
  obj.rot_cos = 1.f;
}


void g2dGetRotationRad(float* radians)
{
  if (radians != NULL) *radians = obj.rot;
}


void g2dGetRotation(float* degrees)
{
  if (degrees != NULL) *degrees = obj.rot * M_180_PI;
}


void g2dSetRotationRad(float radians)
{
  if (radians == obj.rot) return;
  obj.rot = radians;
  obj.rot_sin = sinf(radians);
  obj.rot_cos = cosf(radians);
  if (radians != 0.f) obj_use_rot = true;
}


void g2dSetRotation(float degrees)
{
  g2dSetRotationRad(degrees * M_PI_180);
}


void g2dSetRotationRadRelative(float radians)
{
  g2dSetRotationRad(obj.rot + radians);
}


void g2dSetRotationRelative(float degrees)
{
  g2dSetRotationRadRelative(degrees * M_PI_180);
}

// * Crop functions *

void g2dResetCrop()
{
  if (obj_tex == NULL) return;
  obj.crop_x = 0;
  obj.crop_y = 0;
  obj.crop_w = obj_tex->w;
  obj.crop_h = obj_tex->h;
}


void g2dGetCropXY(int* x, int* y)
{
  if (obj_tex == NULL) return;
  if (x != NULL) *x = obj.crop_x;
  if (y != NULL) *y = obj.crop_y;
}


void g2dGetCropWH(int* w, int* h)
{
  if (obj_tex == NULL) return;
  if (w != NULL) *w = obj.crop_w;
  if (h != NULL) *h = obj.crop_h;
}


void g2dSetCropXY(int x, int y)
{
  if (obj_tex == NULL) return;
  obj.crop_x = x;
  obj.crop_y = y;
}


void g2dSetCropWH(int w, int h)
{
  if (obj_tex == NULL) return;
  obj.crop_w = w;
  obj.crop_h = h;
}


void g2dSetCropXYRelative(int x, int y)
{
  if (obj_tex == NULL) return;
  g2dSetCropXY(obj.crop_x + x, obj.crop_y + y);
}


void g2dSetCropWHRelative(int w, int h)
{
  if (obj_tex == NULL) return;
  g2dSetCropWH(obj.crop_w + w, obj.crop_h + h);
}

// * Texture functions *

void g2dResetTex()
{
  if (obj_tex == NULL) return;
  obj_use_tex_repeat = false;
  obj_use_tex_linear = true;
  if (obj_tex->can_blend) obj_use_blend = true;
}


void g2dSetTexRepeat(bool use)
{
  if (obj_tex == NULL) return;
  obj_use_tex_repeat = use;
}


void g2dSetTexBlend(bool use)
{
  if (obj_tex == NULL) return;
  if (!obj_tex->can_blend) return;
  obj_use_blend = use;
}


void g2dSetTexLinear(bool use)
{
  if (obj_tex == NULL) return;
  obj_use_tex_linear = use;
}

// * Texture management *

void g2dTexFree(g2dImage** tex)
{
  if (tex == NULL) return;
  if (*tex == NULL) return;
  glDeleteTextures(1,&(*tex)->id);
  free(*tex);
  *tex = NULL;
}

static g2dImage* _g2dTexFromSDLSurface(SDL_Surface* surface)
{
  SDL_Surface *gl_surface = NULL;

  if (!surface) return NULL;
  if (!start) _g2dStart();

  g2dImage* tex = (g2dImage*)malloc(sizeof(g2dImage));
  if (!tex) return NULL;

  SDL_PixelFormat format = *(surface->format);
  format.BitsPerPixel = 32;
  format.BytesPerPixel = 4;
  format.Rmask = 0x000000ff;
  format.Gmask = 0x0000ff00;
  format.Bmask = 0x00ff0000;
  format.Amask = 0xff000000;

  gl_surface = SDL_ConvertSurface(surface,&format,0);
  tex->w = gl_surface->w;
  tex->h = gl_surface->h;
  tex->can_blend = 1;

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, gl_surface->w,
               gl_surface->h, 0, GL_RGBA,GL_UNSIGNED_BYTE,
               gl_surface->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  SDL_FreeSurface(gl_surface);
  SDL_FreeSurface(surface);

  return tex;
}

g2dImage* g2dTexLoad(char path[], g2dTex_Mode mode)
{
  if (!path) return NULL;

  return _g2dTexFromSDLSurface(IMG_Load(path));
}

g2dImage* g2dTexFromFont(TTF_Font* font, char text[], g2dColor color)
{
  if (!font) return NULL;

  SDL_Color sdl_color;
  sdl_color.r = G2D_GET_R(color);
  sdl_color.g = G2D_GET_G(color);
  sdl_color.b = G2D_GET_B(color);

  return _g2dTexFromSDLSurface(TTF_RenderUTF8_Blended(font, text, sdl_color));
}

// * Scissor functions *

void g2dResetScissor()
{
  g2dSetScissor(0,0,G2D_SCR_W,G2D_SCR_H);
  scissor = false;
}


void g2dSetScissor(int x, int y, int w, int h)
{
  glScissor(x,G2D_SCR_H-y-h,w,h);
  scissor = true;
}

// EOF
