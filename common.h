// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef COMMON_H
#define COMMON_H

// *
//#define DEBUG
// *

#define EXCEPTION_ARG "Wrong number of arguments\n"
#define EXCEPTION_NEXT_LVL "Next level not defined\n"
#define EXCEPTION -1
#define ERROR_LEN 2048

extern int thread_block;
extern int thread_disp_waiting;
extern int exit_state;
extern char exit_err[ERROR_LEN];
extern char cwd[512];

#define BASIC_SIZE 16
#define AIR_FRICTION 1.008f
#define OBJ_FRICTION 1.085f
#define OBJ_JUMP 2.8f
#define OBJ_CST_JUMP 0.07f
#define OBJ_BIG_JUMP 6.3f
#define OBJ_VT 0.87f // Velocity transfert
#define OBJ_BOUNCE 0.2f
#define OBJ_BREAK 0.35f

#define P_SIZE 12
#define P_ACCEL 0.178f
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
