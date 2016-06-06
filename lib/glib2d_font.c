/*
 * gLib2D_font
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

#include "glib2d_font.h"

/* Number of textures the cache can hold. It must be at least equal to the
 * number of lines rendered per context, otherwise glitches will happen. */
#define TEX_CACHE_SIZE    (32)

/* Object properties of the text being drawn */
typedef struct
{
  float x, y;
  float rot;
  float scale;
  g2dColor color;
  g2dAlpha alpha;
} g2dFontObject;

typedef struct
{
  int age;
  g2dFont *font;
  char *text;
  g2dTexture *tex;
} g2dFontTexCacheLine;

/* Text rendering context */
typedef struct
{
  g2dFont *font;
  char *text;
  g2dFontObject **obj_list;
  int obj_nbr;
  g2dFontObject obj;
  g2dCoord_Mode obj_coord_mode;
} g2dFontContext;

/* A text can contain several lines */
typedef struct
{
  g2dTexture *tex;
  int ypad;
} g2dFontLine;

static bool init = false;
static g2dFontContext *ctx = NULL;
static g2dFontTexCacheLine tex_cache[TEX_CACHE_SIZE];

// * Internal functions *

static void g2dFontTexCacheInit()
{
  int i;

  for (i = 0; i < TEX_CACHE_SIZE; i++) {
    tex_cache[i].age = 0;
    tex_cache[i].font = NULL;
    tex_cache[i].text = NULL;
    tex_cache[i].tex = NULL;
  }
}

static g2dTexture *g2dFontTexCacheInsert(g2dFont *font, char *text)
{
  int i, j;
  SDL_Color color = {255, 255, 255};

  /* Search for oldest texture */
  for (i = 0, j = 0; i < TEX_CACHE_SIZE; i++) {
    if (tex_cache[i].age > tex_cache[j].age) {
      j = i;
    }
  }

  if (tex_cache[j].text) {
    free(tex_cache[j].text);
    g2dTexFree(&tex_cache[j].tex);
  }

  tex_cache[j].age = 0;
  tex_cache[j].font = font;
  tex_cache[j].text = strdup(text);
  tex_cache[j].tex = g2dTexFromSDLSurface(
    TTF_RenderUTF8_Blended(font->ttf, text, color)
  );

  return tex_cache[j].tex;
}

static g2dTexture *g2dFontTexCacheGet(g2dFont *font, char *text)
{
  int i;
  g2dTexture *tex = NULL;

  /* Search while incrementing ages */
  for (i = 0; i < TEX_CACHE_SIZE; i++) {
    tex_cache[i].age++;

    if (tex_cache[i].font == font && strcmp(tex_cache[i].text, text) == 0) {
      tex = tex_cache[i].tex;
      tex_cache[i].age = 0;
    }
  }

  return tex;
}

static g2dFontLine *g2dFontGenLines(int *size, g2dFontContext *ctx)
{
  g2dFontLine *lines = NULL;
  char *dtext;
  int i, j, len, yskip;
  int break_count = 0;
  int line_count = 0;

  dtext = strdup(ctx->text);
  len = strlen(dtext);
  yskip = TTF_FontLineSkip(ctx->font->ttf) / 1.4f;

  for (i = 0, j = 0; i <= len; i++) {
    if (dtext[i] == '\n' || dtext[i] == '\0') {
      if (i <= j) {
        /* Found an empty line */
        dtext[i] = ' ';
      }
      else {
        char *text;

        /* Found a non-empty line. Fetch from cache and add to the list */
        dtext[i] = '\0';
        text = &dtext[j];

        lines = realloc(lines, (line_count + 1) * sizeof(g2dFontLine));
        lines[line_count].tex = g2dFontTexCacheGet(ctx->font, text);
        if (!lines[line_count].tex) {
          lines[line_count].tex = g2dFontTexCacheInsert(ctx->font, text);
        }
        lines[line_count].ypad = yskip * break_count;

        j = i + 1;
        line_count++;
      }

      break_count++;
    }
  }

  free(dtext);

  *size = line_count;
  return lines;
}

static void g2dFontDrawLines(g2dFontContext *ctx)
{
  g2dFontLine *lines;
  int size;
  int i, j;

  lines = g2dFontGenLines(&size, ctx);

  for (i = 0; i < size; i++) {
    g2dBeginRects(lines[i].tex);
    for (j = 0; j < ctx->obj_nbr; j++) {
      g2dFontObject *obj = ctx->obj_list[j];

      if (G2D_GET_A(obj->color) * obj->alpha > 0) {
        g2dSetCoordMode(ctx->obj_coord_mode);
        g2dSetCoordXY(obj->x, obj->y);
        g2dSetScale(obj->scale, obj->scale);
        g2dSetAlpha(obj->alpha);
        g2dSetRotationRad(obj->rot);
        g2dSetColor(obj->color);
        g2dSetCoordXYRelative(0, lines[i].ypad);
        g2dAdd();
      }
    }
    g2dEnd();
  }

  free(lines);
}

// * Exposed functions *

void g2dFontInit()
{
  if (TTF_Init() != 0)
    return;

  g2dFontTexCacheInit();

  init = true;
}

void g2dFontTerm()
{
  TTF_Quit();

  init = false;
}

g2dFont *g2dFontLoad(char *path, int pt)
{
  g2dFont *font;
  TTF_Font *ttf;

  ttf = TTF_OpenFont(path, pt);
  if (!ttf)
    return NULL;

  font = malloc(sizeof(g2dFont));
  if (!font) {
    TTF_CloseFont(font->ttf);
    return NULL;
  }

  font->ttf = ttf;

  return font;
}

void g2dFontFree(g2dFont *font)
{
  if (!font)
    return;

  TTF_CloseFont(font->ttf);

  free(font);
}

void g2dFontBegin(g2dFont *font, char *text)
{
  if (!init || !font)
    return;

  ctx = malloc(sizeof(g2dFontContext));
  ctx->font = font;
  ctx->text = text;
  ctx->obj_list = NULL;
  ctx->obj_nbr = 0;
  ctx->obj_coord_mode = G2D_UP_LEFT;

  g2dFontReset();
}

void g2dFontEnd()
{
  int i;

  if (!ctx)
    return;

  g2dFontDrawLines(ctx);

  for (i = 0; i < ctx->obj_nbr; i++)
    free(ctx->obj_list[i]);

  free(ctx->obj_list);
  free(ctx);
  ctx = NULL;
}

void g2dFontAdd()
{
  if (!ctx)
    return;

  ctx->obj_list = realloc(ctx->obj_list, (ctx->obj_nbr + 1) * sizeof(g2dFontObject*));
  ctx->obj_list[ctx->obj_nbr] = malloc(sizeof(g2dFontObject));
  memcpy(ctx->obj_list[ctx->obj_nbr], &ctx->obj, sizeof(g2dFontObject));
  ctx->obj_nbr++;
}

void g2dFontReset()
{
  g2dFontSetCoordXY(0.f, 0.f);
  g2dFontSetScale(1.f);
  g2dFontSetColor(WHITE);
  g2dFontSetAlpha(255);
  g2dFontSetRotation(0.f);
  g2dFontSetCoordMode(G2D_UP_LEFT);
}

void g2dFontSetCoordMode(g2dCoord_Mode mode)
{
  if (!ctx || mode > G2D_CENTER)
    return;

  ctx->obj_coord_mode = mode;
}

void g2dFontSetCoordXY(float x, float y)
{
  if (!ctx)
    return;

  ctx->obj.x = x;
  ctx->obj.y = y;
}

void g2dFontSetCoordXYRelative(float x, float y)
{
  if (!ctx)
    return;

  ctx->obj.x += x;
  ctx->obj.y += y;
}

void g2dFontSetScale(float scale)
{
  if (!ctx)
    return;

  ctx->obj.scale = scale;
}

void g2dFontSetColor(g2dColor color)
{
  if (!ctx)
    return;

  ctx->obj.color = color;
}

void g2dFontSetAlpha(g2dAlpha alpha)
{
  if (!ctx)
    return;

  if (alpha < 0)
    alpha = 0;
  else if (alpha > 255)
    alpha = 255;

  ctx->obj.alpha = alpha;
}

void g2dFontSetRotation(float degrees)
{
  g2dFontSetRotationRad(degrees * 3.14159f / 180.f);
}

void g2dFontSetRotationRad(float radians)
{
  if (!ctx)
    return;

  ctx->obj.rot = radians;
}

// EOF
