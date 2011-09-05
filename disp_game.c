// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <pspgu.h>

#include "level.h"
#include "game.h"
#include "disp.h"

#include "lib/glib2d.h"
#include "lib/glibvfpu.h"

Camera cam = {1,0.f,0.f,0.f,0.f,1.f,1.f};

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
    g2dPop();
    g2dSetCoordXY(G2D_SCR_W/2,G2D_SCR_H/2);
    g2dSetRotation(-cam.rot);
    g2dSetGlobalScale(cam.zoom);
    g2dSetCoordXYRelative(-gvfpu_floor(cam.x),-gvfpu_floor(cam.y));
    g2dPush();
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
  return (!((x[0] < 0 || x[0] > G2D_SCR_W || y[0] < 0 || y[0] > G2D_SCR_H) &&
            (x[1] < 0 || x[1] > G2D_SCR_W || y[1] < 0 || y[1] > G2D_SCR_H) &&
            (x[2] < 0 || x[2] > G2D_SCR_W || y[2] < 0 || y[2] > G2D_SCR_H) &&
            (x[3] < 0 || x[3] > G2D_SCR_W || y[3] < 0 || y[3] > G2D_SCR_H)));
}


// TODO shadowmaps
/*void renderShadowMask()
{
  g2dClear(G2D_MODULATE(WHITE,127,255));
  _g2dFinish();

  sceGuCopyImage(GU_PSM_8888,0,0,480,272,512,g2d_draw_buffer.data,
                 0,0,512,rendertarget.data);
  _g2dStart();
  sceGuTexSync();
}


void drawShadowMask()
{
  sceGuBlendFunc(GU_ADD,GU_DST_COLOR,GU_FIX,0,0);
  
  g2dBeginRects(&rendertarget);
    g2dSetScaleWH(240,136);
    g2dAdd();
  g2dEnd();
  
  sceGuBlendFunc(GU_ADD,GU_SRC_ALPHA,GU_ONE_MINUS_SRC_ALPHA,0,0);
}*/


void drawLevel()
{
  int i, ty;
  g2dBeginRects(img.tileset);
    g2dPop();
    g2dPush();
    g2dSetTexLinear(false);
    g2dSetTexRepeat(false);
    
    // Objects
    Object* obj_i = lvl.obj_list;
    for (i=0; i!=lvl.obj_nbr; i++, obj_i++)
    {
      g2dPush();
      g2dSetCoordXYRelative(obj_i->x,obj_i->y);
      
      if (isVisible(obj_i))
      {
        g2dSetScaleWH(obj_i->w,obj_i->h);
        g2dSetCropWH(obj_i->type->tex_w,obj_i->type->tex_h);
        ty = obj_i->type->tex_y + obj_i->type->tex_h * obj_i->state;
        g2dSetCropXY(obj_i->type->tex_x,ty);
        g2dAdd();
      }
      
      g2dPop();
    }
    
    // Rays
    if (lvl.ray_list != NULL)
    {
      Ray* ray_i = lvl.ray_list;
      for (i=0; i!=lvl.ray_nbr; i++, ray_i++)
      {
        if (ray_i->dir == 0)
          g2dSetCoordMode(G2D_DOWN_LEFT);
        else if (ray_i->dir == 3)
          g2dSetCoordMode(G2D_UP_RIGHT);
        else
          g2dSetCoordMode(G2D_UP_LEFT);        
        g2dPush();
        g2dSetCoordXYRelative(ray_i->x,ray_i->y);
        g2dSetScaleWH(ray_i->w,ray_i->h);
        g2dSetCropWH((ray_i->dir%2 == 0) ? ray_i->type->tex_w : 1.f,
                     (ray_i->dir%2 == 1) ? ray_i->type->tex_h : 1.f);
        ty = ray_i->type->tex_y + ray_i->type->tex_h * (ray_i->dir%2 == 0);
        g2dSetCropXY(ray_i->type->tex_x,ty);
        g2dAdd();
        g2dPop();
      } 
    }
  
  g2dEnd();
  
  g2dSetGlobalScale(1.f);
}

// EOF
