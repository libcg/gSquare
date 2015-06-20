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

#include <math.h>
#include <time.h>

#include "level.h"
#include "game.h"
#include "lua.h"
#include "audio.h"

Object* obj_ext;
static int obj_nbr;

void updatePosition(Object* obj, float t)
{
  obj->x += t * obj->vx;
  obj->y += t * obj->vy;
}


int collide(const Object* a, const Object* b)
{
  return ((a->x + a->w > b->x && a->x < b->x + b->w) &&
          (a->y + a->h > b->y && a->y < b->y + b->h));
}


int timedCollide(const Object* a, const Object* b, float t)
{
  Object ta = *a, tb = *b;
  updatePosition(&ta,t);
  updatePosition(&tb,t);
        
  return collide(&ta,&tb);
}

// *

// This function assumes the two objects are not actually colliding.
void bounce(Object* obj, Object* obj_col, float t)
{
  int cx = 0, cy = 0;
  float s_diff = 0.f;
  Object tobj_col = *obj_col;
  updatePosition(&tobj_col,t);
  
  // Which side is colliding in each axis ?
  if (tobj_col.y + tobj_col.h > obj->y &&
      obj->y + obj->h > tobj_col.y)
  {
    if  (tobj_col.x + tobj_col.w <= obj->x) cx = -1;
    else if (obj->x + obj->w <= tobj_col.x) cx =  1;
  }
  if (tobj_col.x + tobj_col.w > obj->x &&
      obj->x + obj->w > tobj_col.x)
  {
    if  (tobj_col.y + tobj_col.h <= obj->y) cy = -1;
    else if (obj->y + obj->h <= tobj_col.y) cy =  1;
  }
  
  if (cx)
  {
    // Update per-object collision info
    obj->collide_x = cx;
    obj->collide_x_properties |= obj_col->type->properties;
   
    // Bounce
    if ((cx < 0 && (obj->vx-tobj_col.vx) < 0.f) ||
        (cx > 0 && (obj->vx-tobj_col.vx) > 0.f))
    {
      float v = obj->vx, cv = obj_col->vx;
      obj->vx = OBJ_VT * cv - (1.f-OBJ_VT) * v;
      if (!(obj_col->type->properties & FIXED))
        obj_col->vx = OBJ_VT * v - (1.f-OBJ_VT) * cv;
    }
    
    // Speed difference
    s_diff = fabs(obj->vx-tobj_col.vx);
  }
  else if (cy)
  {
    // Update per-object collision info
    obj->collide_y = cy;
    obj->collide_y_properties |= obj_col->type->properties;
   
    // Bounce
    if ((cy < 0 && (obj->vy-tobj_col.vy) < 0.f) ||
        (cy > 0 && (obj->vy-tobj_col.vy) > 0.f))
    {
      float v = obj->vy, cv = obj_col->vy;
      obj->vy = OBJ_VT * cv - (1.f-OBJ_VT) * v;
      if (!(obj_col->type->properties & FIXED))
        obj_col->vy = OBJ_VT * v - (1.f-OBJ_VT) * cv;
    }
    
    // Speed difference
    s_diff = fabs(obj->vy-tobj_col.vy);
  }
  
  // The other object is breakable
  if ((obj->type->properties & CAN_BREAK) &&
      (tobj_col.type->properties & BREAKABLE) &&
      s_diff > OBJ_BREAK)
  {
    playSound("break");
    if (obj_col->state < 2) obj_col->state++;
    else deleteObject(findObject(obj_col));
  }
  
  // Touch callback for the object
  if (obj->type->touch_callback[0] != '!')
  {
    obj_ext = obj;
    luaCall(obj->type->touch_callback);
  }
}


float getCollisionPosition(Object* obj, Object** col_list, int size)
{
  int i, j;
  float rt = -1.f, // The last time without collision
        t = -0.5f; // Middle of t-1 and t0
  
  for (i=0; i!=COLLIDE_ITER; i++)
  {
    // Check if there is a collider
    for (j=0; j!=size; j++)
    {
      if (timedCollide(obj,col_list[j],t)) break;
    }
    
    // No collider, save t
    if (j == size) rt = t;
    // Rewind in time if there is a collider, else forward
    t += (j != size ? -1.f : 1.f) / (float)(4 << i);
  }
  
  updatePosition(obj,rt);
    
  return rt;
}


int getColliders(Object* obj, Object** list, int size)
{
  int i, n;

  for (i=0, n=0; i!=obj_nbr && n<size; i++)
  {
    Object *oobj = lvl.obj_list[i];

    if (oobj == obj)
      continue;
    
    // Add a collider
    if (collide(obj,oobj))
    {
      if (oobj->type->properties & COLLIDE)
      {
        list[n++] = oobj;
      }
      
      // The other object dies by touch
      if ((obj->type->properties & TOUCH_TO_DIE ||
           oobj->type->properties & DEATH_BY_TOUCH) &&
          oobj->death < 1)
      {
        deleteObject(findObject(oobj));
      }
      // The other object kills by touch
      if ((obj->type->properties & DEATH_BY_TOUCH ||
           oobj->type->properties & TOUCH_TO_DIE) &&
         obj->death < 1)
      {
        deleteObject(findObject(obj));
      }
      if (obj->type->properties & PLAYER)
      {
        // Touch callback
        if (oobj->type->touch_callback[0] != '!')
        {
          obj_ext = oobj;
          luaCall(oobj->type->touch_callback);
        }
        // Flying text
        if (oobj->text[0] != '\0' && (oobj->type->properties & TEXT))
        {
          game.flying_text = oobj->text;
        }
      }
    }
  }
  
  return n;
}


// *


int objProperties(Object* obj)
{
  const int gap = 500;

  // Outside-view object
  if ((obj->x < lvl.limit_x0 - gap ||
       obj->x > lvl.limit_x1 + gap ||
       obj->y < lvl.limit_y0 - gap ||
       obj->y > lvl.limit_y1 + gap) &&
      findObject(obj) != P_ID)
  {
    obj->death = 1; // Destroy!
  }

  // Dead object
  if (obj->death > 0)
  {
    deleteObject(findObject(obj));
    return 0;
  }

  // Tick callback
  if (obj->type->tick_callback[0] != '!')
  {
    obj_ext = obj;
    luaCall(obj->type->tick_callback);
  }
  
  return 1;
}


void objDynamics(Object* obj)
{
  // Big jump
  if (obj->collide_x_properties & BIG_JUMP)
  {
    obj->vx -= obj->collide_x * OBJ_BIG_JUMP;
    if (obj->type->properties & PLAYER) playSound("jump");
  }
  if (obj->collide_y_properties & BIG_JUMP)
  {
    obj->vy -= obj->collide_y * OBJ_BIG_JUMP;
    if (obj->type->properties & PLAYER) playSound("jump");
  }

  // Friction
  if (obj->type->properties & FRICTION)
  {
    if (obj->collide_x_properties & FRICTION) obj->vy /= OBJ_FRICTION;
    if (obj->collide_y_properties & FRICTION) obj->vx /= OBJ_FRICTION;
  }

  // Air friction
  if (obj->type->properties & AIR_RESISTANCE)
  {
    obj->vx /= AIR_FRICTION;
    obj->vy /= AIR_FRICTION;
  }

  // Gravity
  if (obj->type->properties & GRAVITY)
  {
    obj->vx += (G / FPS) * game.g_x;
    obj->vy += (G / FPS) * game.g_y;
  }
  
  // Update
  updatePosition(obj,1.f);
}


void objCollisions(Object* obj)
{
  obj->collide_x = 0;
  obj->collide_y = 0;
  obj->collide_x_properties = 0;
  obj->collide_y_properties = 0;
  
  if (!(obj->type->properties & COLLIDE)) return;
  
  float t = 0.f;
  int i, j;
  
  // Get colliding objects (t0)
  Object* col_list[COLLIDER_NBR];
  int col_n = getColliders(obj,col_list,COLLIDER_NBR);
  
  // No colliders, abort
  if (col_n <= 0) return;

  for (i=0; i!=3; i++)
  {
    // Find the exact collide location (tn, -1 < n < 0)
    t = getCollisionPosition(obj,col_list,col_n);
    
    // Calculate the bounce reaction (tn)
    for (j=0; j!=col_n; j++) bounce(obj,col_list[j],t);

    // Forward to t0
    updatePosition(obj,-t);
    
    // Check collision
    for (j=0; j!=col_n; j++)
    {
      if (collide(obj,col_list[j])) break;
    }
    if (j == col_n) break;
  }
  
  // There's still a collision... rewind
  if (j != col_n)
  {
    updatePosition(obj,t);
  }
}


void physics()
{
  // Other stuff
  game.flying_text = NULL;
  initRay(); // Rays are volatile

  obj_nbr = lvl.obj_nbr; // This variable can change during processing.

  // Dynamics and collisions for each object
  int i, j;
  for (i=0; i<obj_nbr; i++)
  {
    Object* obj = lvl.obj_list[i];

    if (!objProperties(obj)) // An object has been deleted
    {
      obj_nbr--;
      continue;
    }

    if (obj->type->properties & FIXED)
    {
      obj->vx = 0.f;
      obj->vy = 0.f;
      continue;
    }
    
    objDynamics(obj);
    objCollisions(obj);
  }
  
  // Rays
  float tl, l;
  for (i=0; i<lvl.ray_nbr; i++)
  {
    Ray* ray = lvl.ray_list[i];
    Object* cobj = NULL;
    tl = l = 1000.f;
    
    for (j=0; j<obj_nbr; j++)
    {
      Object *obj = lvl.obj_list[j];

      if (ray->dir%2 == 1 && // X axis
          obj->y+obj->h > ray->y && obj->y < ray->y+ray->w)
      {
        if (ray->dir == 3 && obj->x + obj->w < ray->x)
        {
          tl = fabs(ray->x - (obj->x + obj->w));
        }
        else if (ray->dir == 1 && ray->x < obj->x)
        {
          tl = fabs(obj->x - ray->x);
        }
      }
      else if (ray->dir%2 == 0 && // Y axis
               obj->x+obj->w > ray->x && obj->x < ray->x+ray->w)
      {
        if (ray->dir == 0 && obj->y + obj->h < ray->y)
        {
          tl = fabs(ray->y - (obj->y + obj->h));
        }
        else if (ray->dir == 2 && ray->y < obj->y)
        {
          tl = fabs(obj->y - ray->y);
        }
      }
      
      if (tl < l)
      {
        l = tl;
        cobj = obj;
      }
    }
    
    if (cobj != NULL) // A collider has been found
    {
      // Kill
      if ((ray->type->properties & TOUCH_TO_DIE) &&
           cobj->death < 1)
      {
        deleteObject(findObject(cobj));
      }
      // Touch callback
      if (cobj->type->touch_callback[0] != '!')
      {
        obj_ext = cobj;
        luaCall(cobj->type->touch_callback);
      }
    }

    // Update ray properties
    if (ray->dir%2 == 0) ray->h = l;
    else ray->w = l;
  }
}

// EOF
