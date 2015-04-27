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

#ifndef GLIB2D_FONT_H
#define GLIB2D_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "glib2d.h"
#include <SDL_ttf.h>

typedef struct
{
  TTF_Font *ttf;
} g2dFont;

void g2dFontInit();
void g2dFontTerm();

g2dFont *g2dFontLoad(char *path, int pt);
void g2dFontFree(g2dFont *font);

void g2dFontBegin(g2dFont *font, char *text);
void g2dFontEnd();
void g2dFontAdd();

void g2dFontReset();
void g2dFontSetCoordMode(g2dCoord_Mode mode);
void g2dFontSetCoordXY(float x, float y);
void g2dFontSetScale(float scale);
void g2dFontSetColor(g2dColor color);
void g2dFontSetAlpha(g2dAlpha alpha);
void g2dFontSetRotation(float degrees);
void g2dFontSetRotationRad(float radians);

#ifdef __cplusplus
}
#endif

#endif
