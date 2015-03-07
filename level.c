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
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <SDL_timer.h>

#include "level.h"
#include "disp.h"
#include "game.h"
#include "lua.h"
#include "audio.h"

Level lvl = {NULL,0,NULL,0,NULL,0,"","",0,0,0,0,""};

void initObject()
{
  lvl.obj_list = realloc(lvl.obj_list,OBJ_LIST_SIZE * sizeof(Object));
  lvl.obj_nbr = 0;

  lvl.limit_x0 = 0;
  lvl.limit_x1 = 0;
  lvl.limit_y0 = 0;
  lvl.limit_y1 = 0;
  createObject(0.f,0.f,0.f,0.f,0,P_SIZE,P_SIZE); // Player
  game.g_lock = false; // Gravity not locked by default.
}


void initObjectType()
{
  lvl.obj_type_list = realloc(lvl.obj_type_list,
                              OBJ_TYPE_LIST_SIZE * sizeof(Object_Type));
  lvl.obj_type_nbr = 0;

  Object_Type player;
  player.tex_w = P_SIZE;
  player.tex_h = P_SIZE;
  player.tex_x = 0;
  player.tex_y = 0;
  player.properties = GRAVITY + COLLIDE + FRICTION + CAN_BREAK +
                      AIR_RESISTANCE + PLAYER;
  player.touch_callback[0] = '!';
  player.tick_callback[0] = '!';
  createObjectType(player);
}


void initRay()
{
  lvl.ray_list = realloc(lvl.ray_list,RAY_LIST_SIZE * sizeof(Object));
  lvl.ray_nbr = 0;
}


int createObject(float x, float y, float s_x, float s_y,
                 int obj_type_id, float w, float h)
{
  if (lvl.obj_list == NULL) initObject();

  if (lvl.obj_nbr < OBJ_LIST_SIZE) lvl.obj_nbr++;  
  Object* obj = lvl.obj_list + lvl.obj_nbr - 1;
  
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
  obj->type = lvl.obj_type_list + obj_type_id;
  obj->death = 0;
  obj->state = 0;
  obj->text[0] = '\0';
  memset(obj->reg,0,16*sizeof(float));
  
  // Change limits if needed
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
  
  return lvl.obj_nbr-1;
}


int createObjectAligned(float x, float y, float s_x, float s_y,
                        int obj_type_id, float w, float h, int align)
{
  // Center it on the grid
  x += align/2 - w/2;
  y += align/2 - h/2;
  
  return createObject(x,y,s_x,s_y,obj_type_id,w,h);
}


int createObjectType(Object_Type obj_type)
{
  if (lvl.obj_type_list == NULL) initObjectType();

  if (lvl.obj_type_nbr < OBJ_TYPE_LIST_SIZE) lvl.obj_type_nbr++;  
  
  memcpy(lvl.obj_type_list+lvl.obj_type_nbr-1,&obj_type,sizeof(Object_Type));
  
  return lvl.obj_type_nbr-1;
}


int createRay(float x, float y, float size, int dir, int obj_type_id)
{
  if (lvl.ray_list == NULL) initRay();

  if (lvl.ray_nbr < RAY_LIST_SIZE) lvl.ray_nbr++;  
  Ray* ray = lvl.ray_list + lvl.ray_nbr - 1;
  
  ray->x = x;
  ray->y = y;
  ray->w = (dir%2 == 0 ? size : 1);
  ray->h = (dir%2 == 1 ? size : 1);
  ray->dir = dir;
  ray->type = lvl.obj_type_list + obj_type_id;
  
  return lvl.ray_nbr-1;
}


int deleteObject(int obj_id)
{
  if (lvl.obj_list == NULL) initObject();
  if (lvl.obj_nbr <= 0) return -1;

  if (lvl.obj_list[obj_id].type->properties & INVINCIBLE) return 1;

  // This object is the player
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
  if (lvl.obj_list[obj_id].death < 1)
  {
    lvl.obj_list[obj_id].death++;
    return 1;
  }

  int i;
  for (i=obj_id; i!=lvl.obj_nbr-1; i++)
  {
    memcpy(lvl.obj_list+i,lvl.obj_list+i+1,sizeof(Object));
  }
  
  lvl.obj_nbr--;
  
  return 0;
}


int deleteObjectType(int obj_type_id)
{
  if (lvl.obj_type_list == NULL) initObjectType();
  if (lvl.obj_type_nbr <= 0) return -1;
  
  int i;
  for (i=obj_type_id; i!=lvl.obj_type_nbr-1; i++)
  {
    memcpy(lvl.obj_type_list+i,lvl.obj_type_list+i+1,sizeof(Object_Type));
  }
  
  lvl.obj_type_nbr--;
  
  return 0;
}


void objectText(const char* text)
{
  strncpy(lvl.obj_list[lvl.obj_nbr-1].text,text,512);
}


void resetLevel()
{
  #ifdef DEBUG
    luaDoFile(lvl.actual);
  #endif
  luaCall("setLevel");
  luaCall("setGame");
}


void nextLevel()
{
  if (lvl.next[0] == '!')
  {
    g2dTexFree(&img.gsquare);
    setGameState(END);
    img.end = g2dTexLoad("./graphics/end.png",0);
    setFadeMode(&main_fade,FADE_OUT,1);
    SDL_Delay(10000);
    main_fade.color = BLACK;
    setFadeMode(&main_fade,FADE_IN,0);
    exit_state = 1;
    return;
  }
  else
  {
    SDL_Delay(1);
    strcpy(lvl.actual,lvl.next);
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
  }
}


void save()
{
  FILE* fp = fopen("save","w");
  fprintf(fp,"%s",lvl.next);
  fclose(fp);
}

// EOF
