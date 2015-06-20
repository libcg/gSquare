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

#ifndef LEVEL_H
#define LEVEL_H

#include "common.h"

#define LVL_LIMIT_GAP (8*BASIC_SIZE)

enum Obj_Properties
{
  FIXED = 1,
  GRAVITY = 2,
  BIG_JUMP = 4,
  FRICTION = 8,
  DEATH_BY_TOUCH = 16,
  TOUCH_TO_DIE = 32,
  COLLIDE = 64,
  BREAKABLE = 128,
  CAN_BREAK = 256,
  INVINCIBLE = 512,
  AIR_RESISTANCE = 1024,
  PLAYER = 2048,
  TEXT = 4096
};

typedef struct
{
  int tex_x, tex_y;
  int tex_w, tex_h;
  int properties;
  char touch_callback[64];
  char tick_callback[64];
} Object_Type;

typedef struct Object
{
  float x, y;
  float vx, vy;
  float w, h;
  int collide_x, collide_y;
  int collide_x_properties, collide_y_properties;
  int death;
  int state;
  float reg[16];
  char text[512];
  Object_Type* type;
} Object;

typedef struct Ray
{
  float x, y;
  float w, h;
  int dir;
  Object_Type* type;
} Ray;

typedef struct
{
  Object_Type* obj_type_list;
  int obj_type_nbr;
  Object* obj_list;
  int obj_nbr;
  Ray* ray_list;
  int ray_nbr;
  char actual[512], next[512];
  int limit_x0, limit_x1;
  int limit_y0, limit_y1;
  char title[8192];
} Level;

extern Level lvl;

void initObject();
void initObjectType();
void initRay();
int createObject(float x, float y, float s_x, float s_y,
                 int obj_type_id, float w, float h);
int createObjectAligned(float x, float y, float s_x, float s_y,
                        int obj_type_id, float w, float h, int align);
int createObjectType(Object_Type obj_type);
int createRay(float x, float y, float size, int dir, int obj_type_id);
int deleteObject(int obj_id);
int deleteObjectType(int obj_type_id);
void objectText(const char* text);
void resetLevel();
bool nextLevel();
void save();

#endif
