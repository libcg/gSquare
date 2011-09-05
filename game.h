// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef GAME_H
#define GAME_H

#include "level.h"

#define GAMESTATE_STACK_SIZE 64
#define COLLIDE_NBR 128
#define COLLIDER_NBR 4
#define CUR_COL collide_list[collide_nbr]

#define MENU_TITLE_NBR 4
#define PAUSE_CHOICE_NBR 3

enum Game_States { INGAME, DEATH, WIN, TIME_OVER, OUT_OF_BOUNDS,
                   PAUSE, GSQUARE, BANNER, MENU, LEVEL_TITLE, END};
enum Gravity_Dir { N, E, S, W};

typedef struct
{
  float p_x, p_y;
  int g_dir;
} State;

typedef struct
{
  int g_dir, g_lock, g_x, g_y;
  int state;
  int time_elapsed;
  int* state_stack;
  int state_stack_size;
  char* flying_text;
} Game;

typedef struct
{
  int i;
} Pause;

typedef struct
{
  int i, mod_i, state, sub_i, sub_j;
  float rot, rot_target;
  float logo_y, logo_y_target;
  float square_y, square_y_target;
} Menu;

extern Game game;
extern Pause pause;
extern Menu menu;
extern Object* obj_ext;

// Game
void pushGameState(int state);
void popGameState();
void setGameState(int state);
int checkGameState(int state);
int getGameState();
void initGame();
void setPlayerState(float x, float y, int g_dir);
void resetPlayerState();

// Physics
void physics();

#endif
