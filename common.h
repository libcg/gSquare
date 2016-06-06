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

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <SDL_mutex.h>

// *
//#define DEBUG
// *

#define EXCEPTION_ARG "Wrong number of arguments\n"
#define EXCEPTION_NEXT_LVL "Next level not defined\n"
#define EXCEPTION -1
#define ERROR_LEN 2048

extern int exit_state;
extern SDL_sem *logic_sem;
extern SDL_sem *render_sem;

#define BASIC_SIZE 16
#define AIR_FRICTION 1.008f
#define OBJ_FRICTION 1.085f
#define OBJ_JUMP 2.8f
#define OBJ_CST_JUMP 0.07f
#define OBJ_BIG_JUMP 6.3f
#define OBJ_VT 0.87f // Velocity transfert
#define OBJ_BOUNCE 0.2f
#define OBJ_BREAK 0.35f
#define SHADOW_SPEED 0.009f

#define P_SIZE 12
#define P_ACCEL 0.14f
#define P_ID 0
#define P_OBJ (*lvl.obj_list)

#define FADE_TIME 0.8f // s

#define COLLIDE_ITER 7
#define G 9.81f // m/s²
#define METER 16.f // pixels
#define FPS 60.f
#define MALLOC_STEP 50
#define PI 3.14159f

void throwException(const char* err, ...);

#endif
