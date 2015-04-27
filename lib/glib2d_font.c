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

/* Object properties of the text being drawn */
typedef struct
{
  float x, y;
  float rot;
  float scale;
  g2dColor color;
  g2dAlpha alpha;
} g2dFontObject;

/* Text rendering context */
typedef struct
{
  g2dFont *font;
  char *text;
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

// * Internal functions *

static g2dFontLine *g2dFontGenLines(int *size, g2dFontContext *ctx)
{
  g2dFontLine *lines = NULL;
  SDL_Color color = {255, 255, 255};
  char *dtext;
  int i, j, len, yskip;
  int break_count = 0;
  int line_count = 0;

  dtext = strdup(ctx->text);
  len = strlen(dtext);
  yskip = TTF_FontLineSkip(ctx->font->ttf) / 1.4f;

  for (i = 0, j = 0; i <= len; i++) {
    if (dtext[i] == '\n' || dtext[i] == '\0') {
      /* Found a line */
      if (i <= j) {
        /* An empty one */
        dtext[i] = ' ';
      }
      else {
        /* A non-empty one. Render and add to the list */
        dtext[i] = '\0';

        lines = realloc(lines, (line_count + 1) * sizeof(g2dFontLine));
        lines[line_count].tex = g2dTexFromSDLSurface(
          TTF_RenderUTF8_Blended(ctx->font->ttf, &dtext[j], color)
        );
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

static void g2dFontFreeLines(g2dFontLine *lines, int size)
{
  int i;

  for (i = 0; i < size; i++) {
    g2dTexFree(&lines[i].tex);
  }

  free(lines);
}

static void g2dFontDrawLines(g2dFontLine *lines, int size, g2dFontContext *ctx)
{
  int i;

  for (i = 0; i < size; i++) {
    g2dBeginRects(lines[i].tex);
    {
      if (G2D_GET_A(ctx->obj.color) * ctx->obj.alpha > 0) {
        g2dSetCoordMode(ctx->obj_coord_mode);
        g2dSetCoordXY(ctx->obj.x, ctx->obj.y);
        g2dSetScale(ctx->obj.scale, ctx->obj.scale);
        g2dSetAlpha(ctx->obj.alpha);
        g2dSetRotationRad(ctx->obj.rot);
        g2dSetColor(ctx->obj.color);
        g2dSetCoordXYRelative(0, lines[i].ypad);
        g2dAdd();
      }
    }
    g2dEnd();
  }
}

// * Exposed functions *

void g2dFontInit()
{
  if (TTF_Init() != 0)
    return;

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
  ctx->obj_coord_mode = G2D_UP_LEFT;

  g2dFontReset();
}

void g2dFontEnd()
{
  g2dFontLine *lines;
  int size;

  if (!ctx)
    return;

  lines = g2dFontGenLines(&size, ctx);
  if (lines) {
    g2dFontDrawLines(lines, size, ctx);
    g2dFontFreeLines(lines, size);
  }

  free(ctx);
  ctx = NULL;
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
