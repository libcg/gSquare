// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include "controls.h"
#include <SDL_events.h>
#include <string.h>

static char curKey[SDL_NUM_SCANCODES] = {0};
static char oldKey[SDL_NUM_SCANCODES] = {0};

int buttonPressed(unsigned int btn)
{
  return !!curKey[btn];
}


int buttonWasPressed(unsigned int btn)
{
  return !!oldKey[btn];
}


int buttonJustPressed(unsigned int btn)
{
  return buttonPressed(btn) && (!buttonWasPressed(btn));
}


int buttonJustReleased(unsigned int btn)
{
  return !buttonPressed(btn) && buttonWasPressed(btn);
}


void updateControls()
{
  memcpy(oldKey, curKey, sizeof(oldKey));

  // TODO move this to main.c
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      exit(0);
    }
    else if (event.type == SDL_KEYDOWN)
    {
      curKey[event.key.keysym.scancode] = 1;
    }
    else if (event.type == SDL_KEYUP)
    {
      curKey[event.key.keysym.scancode] = 0;
    }
  }
}
