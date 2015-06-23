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

#ifndef CONTROLS_H
#define CONTROLS_H

#include <stdbool.h>

typedef enum
{
  KEY_JUMP = 0,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN,
  KEY_G_LEFT,
  KEY_G_RIGHT,
  KEY_G_INVERT,
  KEY_GO,
  KEY_NO,
  KEY_PAUSE,
  KEY_LAST
} Key;

void ctrlInit();
bool ctrlPressed(Key key);
bool ctrlWasPressed(Key key);
bool ctrlJustPressed(Key key);
bool ctrlJustReleased(Key key);
float ctrlGetPressure(Key key);
void ctrlPoll();

#endif
