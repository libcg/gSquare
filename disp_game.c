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

#include "level.h"
#include "game.h"
#include "disp.h"

#include "lib/glib2d.h"

Camera cam = {1,0.f,0.f,0.f,0.f,1.f,1.f,1.f,1.f};

void setCameraRot(int rot)
{
  int r = (int)(rot - cam.rot_target) % 360;
  if (r < -180) cam.rot_target += r+360;
  else if (r > 180) cam.rot_target += r-360;
  else cam.rot_target += r;  
}


void camera()
{
  // Camera center too far from player
  if (cam.active && lvl.obj_nbr != 0)
  {
    if (cam.x-P_OBJ.x > CAM_STEP) cam.x_target = P_OBJ.x+CAM_STEP;
    else if (P_OBJ.x-cam.x > CAM_STEP) cam.x_target = P_OBJ.x-CAM_STEP;
    if (cam.y-P_OBJ.y > CAM_STEP) cam.y_target = P_OBJ.y+CAM_STEP;
    else if (P_OBJ.y-cam.y > CAM_STEP) cam.y_target = P_OBJ.y-CAM_STEP;
  }
  
  // Camera physics
  cam.x += (cam.x_target-cam.x) * CAM_POS_SPEED;
  cam.y += (cam.y_target-cam.y) * CAM_POS_SPEED;
  cam.rot += (cam.rot_target-cam.rot) * CAM_ROT_SPEED;
  cam.zoom += (cam.zoom_target-cam.zoom) * CAM_ZOOM_SPEED;
  
  // Place the camera
  g2dBeginRects(NULL);
  {
    g2dPop();
    g2dSetCoordXY(g2dScrW()/2,g2dScrH()/2);
    g2dSetRotation(-cam.rot);
    g2dSetGlobalScale(cam.zoom);
    g2dSetCoordXYRelative(-cam.x,-cam.y);
    g2dPush();
  }
  g2dEnd();
}


int isVisible(Object* obj)
{
  float x[4], y[4];
  // Get first corner's position
  g2dGetCoordXYZ(&x[0],&y[0],NULL);
  g2dPush();
  // Get second corner's position
  g2dSetCoordXYRelative(obj->w,0.f);
  g2dGetCoordXYZ(&x[1],&y[1],NULL);
  // Get third corner's position
  g2dSetCoordXYRelative(0.f,obj->h);
  g2dGetCoordXYZ(&x[2],&y[2],NULL);
  // Get fourth corner's position
  g2dSetCoordXYRelative(-obj->w,0.f);
  g2dGetCoordXYZ(&x[3],&y[3],NULL);
  g2dPop();
  // Check if the whole object is off-screen.
  return (!((x[0] < 0 || x[0] > g2dScrW() || y[0] < 0 || y[0] > g2dScrH()) &&
            (x[1] < 0 || x[1] > g2dScrW() || y[1] < 0 || y[1] > g2dScrH()) &&
            (x[2] < 0 || x[2] > g2dScrW() || y[2] < 0 || y[2] > g2dScrH()) &&
            (x[3] < 0 || x[3] > g2dScrW() || y[3] < 0 || y[3] > g2dScrH())));
}


void drawLevel()
{
  static float shadow_x = 0.f;
  int i;

  shadow_x += SHADOW_SPEED;

  g2dBeginRects(img.tileset);
  {
    g2dPop();
    g2dPush();
    g2dSetTexLinear(false);
    g2dSetTexRepeat(false);
    g2dSetCoordInteger(true);
    
    // Objects
    for (i=0; i!=lvl.obj_nbr; i++)
    {
      Object *obj = &lvl.obj_list[i];

      g2dPush();
      g2dSetCoordXYRelative(obj->x,obj->y);

      if (isVisible(obj))
      {
        g2dSetScaleWH(obj->w,obj->h);
        g2dSetCropWH(obj->type->tex_w,obj->type->tex_h);
        g2dSetCropXY(obj->type->tex_x,
                     obj->type->tex_y + (obj->type->tex_h) * obj->state);
        g2dSetColor(G2D_MODULATE(WHITE,
                    255+30*(-1+sinf(shadow_x+obj->x/50.f+obj->y/120.f)),
                    255));
        g2dAdd();
      }

      g2dPop();
    }
    
    // Rays
    if (lvl.ray_list != NULL)
    {
      for (i=0; i!=lvl.ray_nbr; i++)
      {
        Ray *ray = &lvl.ray_list[i];

        if (ray->dir == 0)
          g2dSetCoordMode(G2D_DOWN_LEFT);
        else if (ray->dir == 3)
          g2dSetCoordMode(G2D_UP_RIGHT);
        else
          g2dSetCoordMode(G2D_UP_LEFT);

        g2dPush();
        g2dSetCoordXYRelative(ray->x,ray->y);
        g2dSetScaleWH(ray->w,ray->h);
        g2dSetCropWH(ray->type->tex_w, ray->type->tex_h);
        g2dSetCropXY(ray->type->tex_x,
                     ray->type->tex_y + ray->type->tex_h * (ray->dir%2 == 0));
        g2dSetColor(WHITE);
        g2dAdd();
        g2dPop();
      } 
    }
  }
  g2dEnd();
  
  g2dSetGlobalScale(1.f);
}

// EOF
