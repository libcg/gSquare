// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <pspkernel.h>
#include <math.h>
#include <time.h>

#include "level.h"
#include "game.h"
#include "lua.h"
#include "disp.h"
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
    else deleteObject(obj_col - lvl.obj_list);
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
  int j, n;
  Object* obj_j;
  
  for (j=0, n=0, obj_j = lvl.obj_list; j!=obj_nbr && n<size; j++, obj_j++)
  {
    if (obj-lvl.obj_list == j) continue;
    
    // Add a collider
    if (collide(obj,obj_j))
    {
      if (obj_j->type->properties & COLLIDE)
      {
        list[n++] = obj_j;
      }
      
      // The other object dies by touch
      if ((obj->type->properties & TOUCH_TO_DIE ||
           obj_j->type->properties & DEATH_BY_TOUCH) &&
          obj_j->death < 1)
      {
        deleteObject(obj_j - lvl.obj_list);
      }
      // The other object kills by touch
      if ((obj->type->properties & DEATH_BY_TOUCH ||
           obj_j->type->properties & TOUCH_TO_DIE) &&
         obj->death < 1)
      {
        deleteObject(obj - lvl.obj_list);
      }
      if (obj->type->properties & PLAYER)
      {
        // Touch callback
        if (obj_j->type->touch_callback[0] != '!')
        {
          obj_ext = obj_j;
          luaCall(obj_j->type->touch_callback);
        }
        // Flying text
        if (obj_j->text[0] != '\0' && (obj_j->type->properties & TEXT))
        {
          game.flying_text = obj_j->text;
        }
      }
    }
  }
  
  return n;
}


// *


int objProperties(Object* obj)
{
  // Outside-view object
  if ((obj->x < lvl.limit_x0 - G2D_SCR_W ||
       obj->x > lvl.limit_x1 + G2D_SCR_W ||
       obj->y < lvl.limit_y0 - G2D_SCR_H ||
       obj->y > lvl.limit_y1 + G2D_SCR_H) &&
      obj != lvl.obj_list)
  {
    obj->death = 1; // Destroy!
  }

  // Dead object
  if (obj->death > 0)
  {
    deleteObject(obj - lvl.obj_list);
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
  Object* obj_i;
  for (i=0, obj_i = lvl.obj_list; i<obj_nbr; i++, obj_i++)
  {
    if (!objProperties(obj_i)) // An object has been deleted
    {
      obj_nbr--;
      continue;
    }

    if (obj_i->type->properties & FIXED)
    {
      obj_i->vx = 0.f;
      obj_i->vy = 0.f;
      continue;
    }
    
    objDynamics(obj_i);
    objCollisions(obj_i);
  }
  
  // Rays
  float tl, l;
  Ray* ray_i;
  Object *obj_j, *cobj;
  for (i=0, ray_i = lvl.ray_list; i<lvl.ray_nbr; i++, ray_i++)
  {
    cobj = NULL;
    tl = l = 1000.f;
    
    for (j=0, obj_j = lvl.obj_list; j<obj_nbr; j++, obj_j++)
    {
      if (ray_i->dir%2 == 1 && // X axis
          obj_j->y+obj_j->h > ray_i->y && obj_j->y < ray_i->y+ray_i->w)
      {
        if (ray_i->dir == 3 && obj_j->x + obj_j->w < ray_i->x)
        {
          tl = fabs(ray_i->x - (obj_j->x + obj_j->w));
        }
        else if (ray_i->dir == 1 && ray_i->x < obj_j->x)
        {
          tl = fabs(obj_j->x - ray_i->x);
        }
      }
      else if (ray_i->dir%2 == 0 && // Y axis
               obj_j->x+obj_j->w > ray_i->x && obj_j->x < ray_i->x+ray_i->w)
      {
        if (ray_i->dir == 0 && obj_j->y + obj_j->h < ray_i->y)
        {
          tl = fabs(ray_i->y - (obj_j->y + obj_j->h));
        }
        else if (ray_i->dir == 2 && ray_i->y < obj_j->y)
        {
          tl = fabs(obj_j->y - ray_i->y);
        }
      }
      
      if (tl < l)
      {
        l = tl;
        cobj = obj_j;
      }
    }
    
    if (cobj != NULL) // A collider has been found
    {
      // Kill
      if ((ray_i->type->properties & TOUCH_TO_DIE) &&
           cobj->death < 1)
      {
        deleteObject(cobj - lvl.obj_list);
      }
      // Touch callback
      if (cobj->type->touch_callback[0] != '!')
      {
        obj_ext = cobj;
        luaCall(cobj->type->touch_callback);
      }
    }

    // Update ray properties
    if (ray_i->dir%2 == 0) ray_i->h = l;
    else ray_i->w = l;
  }
}


/*void explode(Object* obj)
{
  Object* obj_i;
  int i;
  for (i=0, obj_i = lvl.obj_list; i<lvl.obj_nbr; i++, obj_i++)
  {
    if (obj == obj_i) continue;
    
    float dist_x = (obj->x + obj->w/2.f) -  (obj_i->x + obj_i->w/2.f),
          dist_y = (obj->y + obj->h/2.f) -  (obj_i->y + obj_i->h/2.f),
          dist = gvfpu_sqrt(dist_x*dist_x + dist_y*dist_y);
    
    if (dist < 100.f)
    {
      if (!deleteObject(obj_i - lvl.obj_list)) obj_i--;
    }
  }
}*/

// EOF
