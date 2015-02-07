// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

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
