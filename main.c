// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "level.h"
#include "disp.h"
#include "game.h"
#include "language.h"
#include "lua.h"
#include "audio.h"
#include "config.h"

int exit_state = 0;

void throwException(const char* err, ...)
{
  fprintf(stderr, "%s",err);
  exit(1);
}

int main(int argc, char* argv[])
{
  configLoad();
  initLanguage();
  initAudio();
  initLua();
  initGame();
  initDisp();

  return 0;
}

// EOF
