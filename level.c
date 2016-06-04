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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL_timer.h>

#include "level.h"
#include "disp.h"
#include "game.h"
#include "lua.h"
#include "audio.h"

Level lvl =
{
  .obj_type_list = NULL,
  .obj_type_nbr = 0,
  .obj_list = NULL,
  .obj_nbr = 0,
  .ray_list = NULL,
  .ray_nbr = 0,
  .next = "",
  .limit_x0 = 0,
  .limit_x1 = 0,
  .limit_y0 = 0,
  .limit_y1 = 0,
  .title = ""
};

void initObject()
{
  for (int i=0; i<lvl.obj_nbr; i++)
    free(lvl.obj_list[i]);

  lvl.obj_list = realloc(lvl.obj_list,0);
  lvl.obj_nbr = 0;

  lvl.limit_x0 = 0;
  lvl.limit_x1 = 0;
  lvl.limit_y0 = 0;
  lvl.limit_y1 = 0;

  // Create player object
  createObject(0.f,0.f,0.f,0.f,0,P_SIZE,P_SIZE);
}


void initObjectType()
{
  for (int i=0; i<lvl.obj_type_nbr; i++)
    free(lvl.obj_type_list[i]);

  lvl.obj_type_list = realloc(lvl.obj_type_list,0);
  lvl.obj_type_nbr = 0;
}


void initRay()
{
  for (int i=0; i<lvl.ray_nbr; i++)
    free(lvl.ray_list[i]);

  lvl.ray_list = realloc(lvl.ray_list,0);
  lvl.ray_nbr = 0;
}


int createObject(float x, float y, float s_x, float s_y,
                 int obj_type_id, float w, float h)
{
  Object* obj = malloc(sizeof(Object));
  if (obj == NULL)
    return -1;

  obj->x = floorf(x);
  obj->y = floorf(y);
  obj->vx = s_x;
  obj->vy = s_y;
  obj->w = w;
  obj->h = h;
  obj->collide_x = 0;
  obj->collide_y = 0;
  obj->collide_x_properties = 0;
  obj->collide_y_properties = 0;
  obj->type = lvl.obj_type_list[obj_type_id];
  obj->death = 0;
  obj->state = 0;
  obj->text[0] = '\0';
  memset(obj->reg,0,16*sizeof(float));
  
  // Change level limits if needed
  if (obj->x-LVL_LIMIT_GAP < lvl.limit_x0) 
  {
    lvl.limit_x0 = obj->x-LVL_LIMIT_GAP;
  }
  else if (obj->x+obj->w+LVL_LIMIT_GAP > lvl.limit_x1)
  {
    lvl.limit_x1 = obj->x+obj->w+LVL_LIMIT_GAP;
  }
  if (obj->y-LVL_LIMIT_GAP < lvl.limit_y0) 
  {
    lvl.limit_y0 = obj->y-LVL_LIMIT_GAP;
  }
  else if (obj->y+obj->h+LVL_LIMIT_GAP > lvl.limit_y1)
  {
    lvl.limit_y1 = obj->y+obj->h+LVL_LIMIT_GAP;
  }

  // Add to the object list
  lvl.obj_nbr++;
  lvl.obj_list = realloc(lvl.obj_list,lvl.obj_nbr * sizeof(Object*));
  lvl.obj_list[lvl.obj_nbr - 1] = obj;

  return lvl.obj_nbr - 1;
}


int createObjectAligned(float x, float y, float s_x, float s_y,
                        int obj_type_id, float w, float h, int align)
{
  // Center it on the grid
  x += align/2 - w/2;
  y += align/2 - h/2;
  
  return createObject(x,y,s_x,s_y,obj_type_id,w,h);
}


int createObjectType(int tex_x, int tex_y, int tex_w, int tex_h, int prop,
                     char* touch_cb, char* tick_cb)
{
  Object_Type* type = malloc(sizeof(Object_Type));
  if (type == NULL)
    return -1;

  type->tex_x = tex_x;
  type->tex_y = tex_y;
  type->tex_w = tex_w;
  type->tex_h = tex_h;
  type->properties = prop;
  strncpy(type->touch_callback,touch_cb,sizeof(type->touch_callback));
  strncpy(type->tick_callback,tick_cb,sizeof(type->tick_callback));

  // Add to the object type list
  lvl.obj_type_nbr++;
  lvl.obj_type_list = realloc(lvl.obj_type_list,lvl.obj_type_nbr * sizeof(Object_Type*));
  lvl.obj_type_list[lvl.obj_type_nbr - 1] = type;

  return lvl.obj_type_nbr - 1;
}


int createRay(float x, float y, float size, int dir, int obj_type_id)
{
  Ray* ray = malloc(sizeof(Ray));
  if (ray == NULL)
    return -1;

  ray->x = x;
  ray->y = y;
  ray->w = (dir%2 == 0 ? size : 1);
  ray->h = (dir%2 == 1 ? size : 1);
  ray->dir = dir;
  ray->type = lvl.obj_type_list[obj_type_id];

  // Add to the ray list
  lvl.ray_nbr++;
  lvl.ray_list = realloc(lvl.ray_list,lvl.ray_nbr * sizeof(Ray*));
  lvl.ray_list[lvl.ray_nbr - 1] = ray;

  return lvl.ray_nbr - 1;
}


int deleteObject(int obj_id)
{
  if (obj_id < 0 || obj_id >= lvl.obj_nbr)
    return -1;

  if (lvl.obj_list[obj_id]->type->properties & INVINCIBLE)
    return 1;

  // This object is the player
  // TODO: delete cb for Lua
  if (obj_id == P_ID)
  {
    if (getGameState() == INGAME)
    {
      playSound("death");
      pushGameState(LOSE);
    }
    return 1;
  }

  // This object will be deleted next time
  // TODO: remove
  if (lvl.obj_list[obj_id]->death < 1)
  {
    lvl.obj_list[obj_id]->death++;
    return 1;
  }

  for (int i=obj_id; i!=lvl.obj_nbr-1; i++)
  {
    lvl.obj_list[i] = lvl.obj_list[i + 1];
  }
  
  lvl.obj_nbr--;
  lvl.obj_list = realloc(lvl.obj_list,lvl.obj_nbr * sizeof(Object*));
  
  return 0;
}


int deleteObjectType(int obj_type_id)
{
  if (obj_type_id < 0 || obj_type_id >= lvl.obj_type_nbr)
    return -1;
  
  for (int i=obj_type_id; i!=lvl.obj_type_nbr-1; i++)
  {
    lvl.obj_type_list[i] = lvl.obj_type_list[i + 1];
  }
  
  lvl.obj_type_nbr--;
  lvl.obj_type_list = realloc(lvl.obj_type_list,lvl.obj_type_nbr * sizeof(Object_Type));
  
  return 0;
}


int findObject(Object *obj)
{
  for (int i=0; i<lvl.obj_nbr; i++)
    if (lvl.obj_list[i] == obj)
      return i;

  return -1;
}


void objectText(const char* text)
{
  strncpy(lvl.obj_list[lvl.obj_nbr-1]->text,text,512);
}


void resetLevel()
{
  luaCall("setLevel");
  luaCall("setGame");

  // Gravity not locked by default
  game.g_lock = false;
}


bool nextLevel()
{
  if (lvl.next[0] == '!')
  {
    setGameState(END);
    setFadeMode(&main_fade,FADE_OUT,1);
    SDL_Delay(10000);
    setFadeMode(&main_fade,FADE_IN,0);
    waitFadeDone(&main_fade);
    setFadeMode(&main_fade,FADE_OUT,0);
    setGameState(MENU);
    menu.state = 0;
    return false;
  }
  else
  {
    luaDoFile(lvl.next); 
    lvl.title[0] = '!';   
    luaCall("getInfo");
    if (lvl.title[0] != '!')
    {
      setGameState(LEVEL_TITLE);
      setMusic("!");
      main_fade.color = WHITE;
      setFadeMode(&main_fade,FADE_OUT,0);
      SDL_Delay(2000);
      setFadeMode(&main_fade,FADE_IN,0);
      waitFadeDone(&main_fade);
      setFadeMode(&main_fade,FADE_OUT,0);
      setGameState(INGAME);
    }
    resetLevel();
    return true;
  }
}


void save()
{
  FILE* fp = fopen("save","w");
  fprintf(fp,"%s",lvl.next);
  fclose(fp);
}

// EOF
