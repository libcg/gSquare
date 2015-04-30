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

static float curKeyPres[KEY_LAST] = {0};
static float oldKeyPres[KEY_LAST] = {0};
static char curCodes[SDL_NUM_SCANCODES] = {0};
static char oldCodes[SDL_NUM_SCANCODES] = {0};

bool ctrlPressed(Key key)
{
  return (curKeyPres[key] > 0.5f);
}


bool ctrlWasPressed(Key key)
{
  return (oldKeyPres[key] > 0.5f);
}


bool ctrlJustPressed(Key key)
{
  return ctrlPressed(key) && !ctrlWasPressed(key);
}


bool ctrlJustReleased(Key key)
{
  return !ctrlPressed(key) && ctrlWasPressed(key);
}

float ctrlGetPressure(Key key)
{
  return curKeyPres[key];
}

void ctrlPoll()
{
  memcpy(oldCodes, curCodes, sizeof(oldCodes));
  memcpy(curCodes, SDL_GetKeyboardState(NULL), sizeof(curCodes));
  memcpy(oldKeyPres, curKeyPres, sizeof(oldKeyPres));

  /* Map keys from keyboard */
  curKeyPres[KEY_JUMP]      = curCodes[SDL_SCANCODE_S];
  curKeyPres[KEY_LEFT]      = curCodes[SDL_SCANCODE_LEFT];
  curKeyPres[KEY_RIGHT]     = curCodes[SDL_SCANCODE_RIGHT];
  curKeyPres[KEY_UP]        = curCodes[SDL_SCANCODE_UP];
  curKeyPres[KEY_DOWN]      = curCodes[SDL_SCANCODE_DOWN];
  curKeyPres[KEY_G_LEFT]    = curCodes[SDL_SCANCODE_A];
  curKeyPres[KEY_G_RIGHT]   = curCodes[SDL_SCANCODE_D];
  curKeyPres[KEY_G_INVERT]  = curCodes[SDL_SCANCODE_A] &&
                              curCodes[SDL_SCANCODE_D];
  curKeyPres[KEY_GO]        = curCodes[SDL_SCANCODE_RETURN];
  curKeyPres[KEY_NO]        = curCodes[SDL_SCANCODE_ESCAPE];
  curKeyPres[KEY_PAUSE]     = curCodes[SDL_SCANCODE_ESCAPE];
}

// EOF
