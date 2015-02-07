// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL_scancode.h>

int buttonPressed(unsigned int btn);
int buttonWasPressed(unsigned int btn);
int buttonJustPressed(unsigned int btn);
int buttonJustReleased(unsigned int btn);
void updateControls();

#endif
