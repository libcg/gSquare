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

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "level.h"
#include "disp.h"
#include "game.h"
#include "language.h"
#include "lua.h"
#include "audio.h"
#include "config.h"
#include "controls.h"

int exit_state = 0;

void throwException(const char* err, ...)
{
  char buf[1024];
  va_list args;

  va_start(args,err);
  vsnprintf(buf,sizeof(buf),err,args);
  va_end(args);

  fprintf(stderr,"%s",buf);
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Exception",buf,NULL);

  exit(1);
}

int main(int argc, char* argv[])
{
  SDL_mutex *mutex;

  mutex = SDL_CreateMutex();
  if (!mutex)
    throwException("Couldn't create mutex");

  configInit();
  configLoad();
  ctrlInit();
  initLanguage();
  initAudio();
  initLua();
  initGame(mutex);
  initDisp(mutex);

  while (!exit_state)
    SDL_Delay(10);

  SDL_DestroyMutex(mutex);

  return 0;
}

// EOF
