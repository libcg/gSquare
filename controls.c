// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include "controls.h"
#include <SDL/SDL.h>
#include <SDL/SDL_events.h>
#include <SDL/SDL_keyboard.h>
#include <string.h>

unsigned char oldKey[SDLK_LAST] = {0}, key[SDLK_LAST] = {0};

int buttonPressed(unsigned int btn)
{
  return (key[btn] ? 1 : 0);
}


int buttonWasPressed(unsigned int btn)
{
  return (oldKey[btn] ? 1 : 0);
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
  memcpy(oldKey, key, SDLK_LAST);

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      exit(0);
    }
    else if (event.type == SDL_KEYDOWN)
    {
      key[event.key.keysym.sym] = 1;
    }
    else if (event.type == SDL_KEYUP)
    {
      key[event.key.keysym.sym] = 0;
    }
  }
}
