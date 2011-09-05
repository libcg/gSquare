// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#ifndef LUA_H
#define LUA_H

// Lua
void initLua();
void luaCall(char* func_name);
void luaDoFile(const char* path);

#endif
