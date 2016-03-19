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

#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "game.h"
#include "level.h"
#include "audio.h"
#include "common.h"
#include "disp.h"
#include "config.h"

#define LUA_EXCEPTION(condition,err)\
  if (condition)\
  { throwException(err);\
    return 0; }

lua_State* lua_state;
char next[64]; 

int luaVarInteger(lua_State* L, int* var)
{
  int n_arg = lua_gettop(L);
  LUA_EXCEPTION(n_arg < 0 || n_arg > 1,EXCEPTION_ARG)

  if (n_arg == 1)
  {
    if (lua_isnumber(L,1)) *var = lua_tointeger(L,1);
  }

  lua_pushinteger(L,*var);
  return 1;
}


int luaVarFloat(lua_State* L, float* var)
{
  int n_arg = lua_gettop(L);
  LUA_EXCEPTION(n_arg < 0 || n_arg > 1,EXCEPTION_ARG)

  if (n_arg == 1)
  {
    if (lua_isnumber(L,1)) *var = lua_tonumber(L,1);
  }

  lua_pushnumber(L,*var);
  return 1;
}

// Game functions

int luaVarPlayerX(lua_State* L)
{
  if (lvl.obj_nbr == 0)
    return 0;

  return luaVarFloat(L,&P_OBJ->x);
}

int luaVarPlayerY(lua_State* L)
{
  if (lvl.obj_nbr == 0)
    return 0;

  return luaVarFloat(L,&P_OBJ->y);
}

int luaVarGravityDir(lua_State* L)
{
  return luaVarInteger(L,&game.g_dir);
}

int luaVarGravityLock(lua_State* L)
{
  return luaVarInteger(L,&game.g_lock);
}

int luaVarTimeElapsed(lua_State* L)
{
  return luaVarInteger(L,&game.time_elapsed);
}

int luaVarExitState(lua_State* L)
{
  return luaVarInteger(L,&exit_state);
}

int luaSetPlayerState(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 3,EXCEPTION_ARG)

  setPlayerState(lua_tonumber(L,1),lua_tonumber(L,2),lua_tointeger(L,3));
  return 0;
}

int luaResetPlayerState(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 0,EXCEPTION_ARG)

  resetPlayerState();
  return 0;
}

int luaPushGameState(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  int state = lua_tointeger(L,1);
  pushGameState(state);
  return 0;
}

int luaSetGameState(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  int state = lua_tointeger(L,1);
  setGameState(state);
  return 0;
}

// Level functions

int luaInitObject(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 0,EXCEPTION_ARG)

  initObject();
  return 0;
}

int luaCreateObject(lua_State* L)
{
  if (lvl.obj_type_nbr == 0) return 0;
  
  if (lua_gettop(L) == 5)
  {
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float s_x = lua_tonumber(L,3);
    float s_y = lua_tonumber(L,4);
    int obj_type_id = lua_tointeger(L,5);
    float w = lvl.obj_type_list[obj_type_id]->tex_w;
    float h = lvl.obj_type_list[obj_type_id]->tex_h;
    createObject(x,y,s_x,s_y,obj_type_id,w,h);
  }
  else if (lua_gettop(L) == 7)
  {
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float s_x = lua_tonumber(L,3);
    float s_y = lua_tonumber(L,4);
    int obj_type_id = lua_tointeger(L,5);
    float w = lua_tonumber(L,6);
    float h = lua_tonumber(L,7);
    createObject(x,y,s_x,s_y,obj_type_id,w,h);
  }
  else throwException(EXCEPTION_ARG);

  return 0;
}

int luaCreateObjectAligned(lua_State* L)
{
  if (lua_gettop(L) == 6)
  {
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float s_x = lua_tonumber(L,3);
    float s_y = lua_tonumber(L,4);
    int obj_type_id = lua_tointeger(L,5);
    float w = lvl.obj_type_list[obj_type_id]->tex_w;
    float h = lvl.obj_type_list[obj_type_id]->tex_h;
    int align = lua_tointeger(L,6);
    createObjectAligned(x,y,s_x,s_y,obj_type_id,w,h,align);
  }
  else if (lua_gettop(L) == 8)
  {
    float x = lua_tonumber(L,1);
    float y = lua_tonumber(L,2);
    float s_x = lua_tonumber(L,3);
    float s_y = lua_tonumber(L,4);
    int obj_type_id = lua_tointeger(L,5);
    float w = lua_tonumber(L,6);
    float h = lua_tonumber(L,7);
    int align = lua_tointeger(L,8);
    createObjectAligned(x,y,s_x,s_y,obj_type_id,w,h,align);
  }
  else throwException(EXCEPTION_ARG);

  return 0;
}

int luaDeleteObject(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  float obj_id = lua_tonumber(L,1);
  deleteObject(obj_id);
  return 0;
}

int luaInitObjectType(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 0,EXCEPTION_ARG)

  initObjectType();
  return 0;
}

int luaCreateObjectType(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 7,EXCEPTION_ARG)

  int tex_x = lua_tointeger(L,1);
  int tex_y = lua_tointeger(L,2);
  int tex_w = lua_tointeger(L,3);
  int tex_h = lua_tointeger(L,4);
  int prop = lua_tointeger(L,5);
  char* touch_cb = lua_tostring(L,6);
  char* tick_cb = lua_tostring(L,7);
  createObjectType(tex_x,tex_y,tex_w,tex_h,prop,touch_cb,tick_cb);
  return 0;
}

int luaDeleteObjectType(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  float obj_type_id = lua_tonumber(L,1);
  deleteObjectType(obj_type_id);
  return 0;
}

int luaCreateRay(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 5,EXCEPTION_ARG)

  float x = lua_tonumber(L,1);
  float y = lua_tonumber(L,2);
  int size = lua_tointeger(L,3);
  int dir = lua_tointeger(L,4);
  int obj_type_id = lua_tointeger(L,5);
  createRay(x,y,size,dir,obj_type_id);
  return 0;
}

int luaSetNextLevel(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  if (!lua_isstring(L,1)) lvl.next[0] = '!';
  else strncpy(lvl.next,lua_tostring(L,1),512);  
  return 0;
}

int luaObjectText(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  if (!lua_isstring(L,1)) objectText("\0");
  else objectText(lua_tostring(L,1));  
  return 0;
}

int luaVarObjX(lua_State* L)
{
  if (obj_ext == NULL) return 0;
  return luaVarFloat(L,&(obj_ext->x));
}

int luaVarObjY(lua_State* L)
{
  if (obj_ext == NULL) return 0;
  return luaVarFloat(L,&(obj_ext->y));
}

int luaVarObjState(lua_State* L)
{
  if (obj_ext == NULL) return 0;
  return luaVarInteger(L,&(obj_ext->state));
}

int luaVarObjDeath(lua_State* L)
{
  if (obj_ext == NULL) return 0;
  return luaVarInteger(L,&(obj_ext->death));
}

int luaVarObjReg(lua_State* L)
{
  if (obj_ext == NULL) return 0;
  int n_arg = lua_gettop(L);
  LUA_EXCEPTION(n_arg < 1 || n_arg > 2,EXCEPTION_ARG)

  int i = 0;
  if (lua_isnumber(L,1)) i = lua_tointeger(L,1);
  if (i < 0 || i >= 16) return 0;

  if (n_arg == 2)
  {
    if (lua_isnumber(L,2)) obj_ext->reg[i] = lua_tonumber(L,2);
  }

  lua_pushnumber(L,obj_ext->reg[i]);
  return 1;
}

int luaVarObjText(lua_State* L)
{
  int n_arg = lua_gettop(L);
  LUA_EXCEPTION(n_arg != 0,EXCEPTION_ARG)
  
  lua_pushstring(L,obj_ext->text);
  return 1;
}

int luaLevelText(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)
  
  strncpy(lvl.title,lua_tostring(L,1),8192);  
  return 0;
}

// Audio functions

int luaSetMusic(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  setMusic(lua_tostring(L,1));
  return 0;
}

int luaLoadSound(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 2,EXCEPTION_ARG)

  loadSound(lua_tostring(L,1),lua_tostring(L,2));
  return 0;
}

int luaFreeSound(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  freeSound(lua_tostring(L,1));
  return 0;
}

int luaPlaySound(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  playSound(lua_tostring(L,1));
  return 0;
}

// Display functions

int luaSetTimerAspect(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 4,EXCEPTION_ARG)

  setTimerAspect(lua_tonumber(L,1),G2D_RGBA(lua_tointeger(L,2),
                                            lua_tointeger(L,3),
                                            lua_tointeger(L,4),255));
  return 0;
}

int luaSetCameraActive(lua_State* L)
{
  LUA_EXCEPTION(lua_gettop(L) != 1,EXCEPTION_ARG)

  cam.active = lua_toboolean(L,1);
  return 0;
}

// Language functions

int luaGetLanguageID(lua_State* L)
{
  Config *cfg = configGet();

  return luaVarInteger(L,&cfg->lang_id);
}

// Common

void luaRegister()
{
  // Game
  lua_register(lua_state,"varPlayerX",luaVarPlayerX);
  lua_register(lua_state,"varPlayerY",luaVarPlayerY);
  lua_register(lua_state,"varGravityDir",luaVarGravityDir);
  lua_register(lua_state,"varGravityLock",luaVarGravityLock);
  lua_register(lua_state,"varTimeElapsed",luaVarTimeElapsed);
  lua_register(lua_state,"varExitState",luaVarExitState);
  lua_register(lua_state,"setPlayerState",luaSetPlayerState);
  lua_register(lua_state,"resetPlayerState",luaResetPlayerState);
  lua_register(lua_state,"pushGameState",luaPushGameState);
  lua_register(lua_state,"setGameState",luaSetGameState);
  // Level
  lua_register(lua_state,"initObject",luaInitObject);
  lua_register(lua_state,"createObject",luaCreateObject);
  lua_register(lua_state,"createObjectAligned",luaCreateObjectAligned);
  lua_register(lua_state,"deleteObject",luaDeleteObject);
  lua_register(lua_state,"initObjectType",luaInitObjectType);
  lua_register(lua_state,"createObjectType",luaCreateObjectType);
  lua_register(lua_state,"deleteObjectType",luaDeleteObjectType);
  lua_register(lua_state,"createRay",luaCreateRay);
  lua_register(lua_state,"setNextLevel",luaSetNextLevel);
  lua_register(lua_state,"objectText",luaObjectText);
  lua_register(lua_state,"varObjX",luaVarObjX);
  lua_register(lua_state,"varObjY",luaVarObjY);
  lua_register(lua_state,"varObjState",luaVarObjState);
  lua_register(lua_state,"varObjDeath",luaVarObjDeath);
  lua_register(lua_state,"varObjReg",luaVarObjReg);
  lua_register(lua_state,"varObjText",luaVarObjText);
  lua_register(lua_state,"levelText",luaLevelText);
  // Audio
  lua_register(lua_state,"setMusic",luaSetMusic);
  lua_register(lua_state,"loadSound",luaLoadSound);
  lua_register(lua_state,"freeSound",luaFreeSound);
  lua_register(lua_state,"playSound",luaPlaySound);
  // Display
  lua_register(lua_state,"setTimerAspect",luaSetTimerAspect);
  lua_register(lua_state,"setCameraActive",luaSetCameraActive);
  // Language
  lua_register(lua_state,"getLanguageID",luaGetLanguageID);
}


void luaCall(char* func_name)
{
  lua_getglobal(lua_state,func_name);
  
  if (!lua_isfunction(lua_state,1))
  {
    lua_pop(lua_state,1);
    throwException("Function not defined (%s)\n",func_name);
  }
  else
  {
    lua_call(lua_state,0,0);
  }
}


void luaDoFile(const char* path)
{
  if (luaL_dofile(lua_state,path) != 0)
  {
    throwException("%s\n",(char*)lua_tostring(lua_state,-1));
  }
}


void initLua()
{
  lua_state = luaL_newstate();
  luaL_openlibs(lua_state);
  luaRegister();
}
