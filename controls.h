// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL_scancode.h>

int ctrlPressed(int btn);
int ctrlWasPressed(int btn);
int ctrlJustPressed(int btn);
int ctrlJustReleased(int btn);
void ctrlNextFrame();

#endif
