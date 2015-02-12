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

#include "controls.h"
#include <SDL_keyboard.h>
#include <string.h>

static char curButton[SDL_NUM_SCANCODES] = {0};
static char oldButton[SDL_NUM_SCANCODES] = {0};

int ctrlPressed(int btn)
{
  return !!curButton[btn];
}


int ctrlWasPressed(int btn)
{
  return !!oldButton[btn];
}


int ctrlJustPressed(int btn)
{
  return ctrlPressed(btn) && (!ctrlWasPressed(btn));
}


int ctrlJustReleased(int btn)
{
  return !ctrlPressed(btn) && ctrlWasPressed(btn);
}


void ctrlNextFrame()
{
  memcpy(oldButton, curButton, sizeof(oldButton));
  memcpy(curButton, SDL_GetKeyboardState(NULL), sizeof(curButton));
}
