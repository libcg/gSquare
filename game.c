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
#include <SDL_timer.h>
#include <SDL_thread.h>

#include "common.h"
#include "game.h"
#include "controls.h"
#include "disp.h"
#include "level.h"
#include "audio.h"
#include "lua.h"
#include "config.h"
#include "language.h"

Game game = {S,0,0.f,0.f,0,{0},0,NULL};
Pause pause = {0};
Menu menu = {0,0,0,0,0,0.f,0.f,0.f,70.f,500.f,350.f};
State p_state;

// Game States

void initGameState()
{
  setMusic("audio/c418-sometimesimakevideogamemusic.mp3");
  #ifdef DEBUG
    setGameState(MENU);
  #else
    setGameState(GSQUARE);
  #endif
}


void pushGameState(int state)
{
  if (game.state_stack_size >= GAMESTATE_STACK_SIZE) return;
  if (getGameState() == state) return;

  game.state_stack[game.state_stack_size++] = state;
}


void popGameState()
{
  if (game.state_stack_size <= 0) return;

  game.state_stack_size--;
}


void setGameState(int state)
{
  game.state_stack_size = 0;
  pushGameState(state);
}


int checkGameState(int state)
{
  int i;
  for (i=0; i!=game.state_stack_size; i++)
  {
    if (game.state_stack[i] == state) return 1;
  }
  return 0;
}


int getGameState()
{
  if (game.state_stack_size <= 0) return -1;
  return game.state_stack[game.state_stack_size-1];
}

// Player states

void setPlayerState(float x, float y, int g_dir)
{
  p_state.p_x = x;
  p_state.p_y = y;
  p_state.g_dir = g_dir;
}


void resetPlayerState()
{
  if (lvl.obj_nbr == 0) return;
  P_OBJ->vx = 0.f;
  P_OBJ->vy = 0.f;
  P_OBJ->x = p_state.p_x;
  P_OBJ->y = p_state.p_y;
  game.g_dir = p_state.g_dir;
}


void gameControls()
{
  static int lose_cnt = 0;

  ctrlPoll();
  
  if (lvl.obj_nbr != 0 && getGameState() == INGAME)
  {
    // Change gravity dir
    if (!game.g_lock)
    {
      int g_inc = ctrlJustPressed(KEY_G_LEFT) -
                  ctrlJustPressed(KEY_G_RIGHT) +
                  2 * ctrlJustPressed(KEY_G_INVERT);
      game.g_dir += g_inc;
    }
    setCameraRot(180 + game.g_dir * 90);
    int g_dir_mod = game.g_dir % 4;
    while (g_dir_mod < 0) g_dir_mod += 4;
    game.g_x = (g_dir_mod == E) - (g_dir_mod == W);
    game.g_y = (g_dir_mod == S) - (g_dir_mod == N);
    
    // Square move
    float dir = ctrlGetPressure(KEY_RIGHT) - ctrlGetPressure(KEY_LEFT);
    P_OBJ->vx += game.g_y * P_ACCEL * dir;
    P_OBJ->vy -= game.g_x * P_ACCEL * dir;
                                   
    // Square jump
    if (ctrlPressed(KEY_JUMP))
    {
      // Impulse
      if (game.g_x)
        P_OBJ->vx += ctrlGetPressure(KEY_JUMP) * OBJ_JUMP * (-P_OBJ->collide_x);
      if (game.g_y)
        P_OBJ->vy += ctrlGetPressure(KEY_JUMP) * OBJ_JUMP * (-P_OBJ->collide_y);
      // Jump higher by holding cross button
      if ((P_OBJ->vx > 0 && game.g_x < 0) ||
          (P_OBJ->vx < 0 && game.g_x > 0))
        P_OBJ->vx += OBJ_CST_JUMP * (-game.g_x);
      if ((P_OBJ->vy > 0 && game.g_y < 0) ||
          (P_OBJ->vy < 0 && game.g_y > 0))
        P_OBJ->vy += OBJ_CST_JUMP * (-game.g_y);
    }
  }
  
  // Game state reset
  switch (getGameState())
  {
    case INGAME:
      P_OBJ->state = 0;
      cam.active = 1;
      lose_cnt = 0;
      if (ctrlJustPressed(KEY_PAUSE))
      {
        pause.i = 0;
        pushGameState(PAUSE);
      }
    break;
    case WIN:
      if (ctrlJustPressed(KEY_GO))
      {
        save();
        waitFadeDone(&ui_fade);
        game.g_lock = 0;

        if (nextLevel())
        {
	        setGameState(INGAME);
	        ui_fade.alpha = 255;
	        if (lvl.obj_nbr != 0)
	        {
	          cam.x = cam.x_target = P_OBJ->x + P_OBJ->w/2.f;
	          cam.y = cam.y_target = P_OBJ->y + P_OBJ->h/2.f;
	        }
	      }
      }
    break;
    case LOSE:
      P_OBJ->state = 1;
      cam.active = 0;
      if (lose_cnt++ == 40)
      {
        resetPlayerState();
        popGameState();
      }
      else if (ctrlJustPressed(KEY_PAUSE))
      {
        pause.i = 0;
        pushGameState(PAUSE);
      }
    break;
    case PAUSE:
      pause.i += ctrlJustPressed(KEY_UP) -
                 ctrlJustPressed(KEY_DOWN);
      if (pause.i < 0) pause.i += PAUSE_CHOICE_NBR;
      else if (pause.i >= PAUSE_CHOICE_NBR) pause.i -= PAUSE_CHOICE_NBR;
      
      if (ctrlJustPressed(KEY_GO))
      {
        popGameState();
        if (pause.i == 1) resetPlayerState();
        if (pause.i == 2) resetLevel();
        if (pause.i == 3) {setGameState(MENU); menu.state = 0;}
      }
     break;
  }
}


void checkBounds()
{
  if (lvl.obj_nbr == 0) return;

  // Check if the player is "out of bounds"
  if (P_OBJ->x < lvl.limit_x0 ||
      P_OBJ->x+P_OBJ->type->tex_w > lvl.limit_x1 ||
      P_OBJ->y < lvl.limit_y0 ||
      P_OBJ->y+P_OBJ->type->tex_h > lvl.limit_y1)
  {
    cam.active = 0;
    pushGameState(LOSE);
  }
}


void gamegSquare()
{
  setFadeMode(&main_fade,FADE_OUT,0);
  waitFadeDone(&main_fade);

  SDL_Delay(3000);

  setFadeMode(&main_fade,FADE_IN,0);
  waitFadeDone(&main_fade);

  setGameState(BANNER);
}


void gameBANNER()
{
  setFadeMode(&main_fade,FADE_OUT,0);
  waitFadeDone(&main_fade);

  SDL_Delay(3000);

  setFadeMode(&main_fade,FADE_IN,0);
  waitFadeDone(&main_fade);

  setGameState(MENU);
  SDL_Delay(50);
}


void gameMenu()
{
  char saved_lvl[512], buffer[512];
  strcpy(saved_lvl,lvl.next);
  FILE* fp = fopen("save","r");
  if (fp != NULL)
  {
    if (fscanf(fp,"%s",buffer) > 0) strcpy(saved_lvl,buffer);
    fclose(fp);
  }
  else
  {
    strcpy(saved_lvl,"./levels/easy1.lua");
    fp = fopen("save","w");
    fprintf(fp,"%s",saved_lvl);
    fclose(fp);
  }
  
  setFadeMode(&main_fade,FADE_OUT,0);
  waitFadeDone(&main_fade);

  int play = 0;
  while (!play)
  {
    ctrlPoll();
    
    if (menu.state == 0) // Where Bluz can rotate
    {
      int i_inc = ctrlJustPressed(KEY_RIGHT) -
                  ctrlJustPressed(KEY_LEFT);
      menu.i += i_inc;
      menu.rot_target = -menu.i * 90;
      menu.mod_i = menu.i % MENU_TITLE_NBR;
      if (menu.mod_i < 0) menu.mod_i += MENU_TITLE_NBR;
      
      if (ctrlJustPressed(KEY_GO))
      {
        menu.sub_i = 0;
        
        if (menu.mod_i < 3) // Story, Options, Credits
        {
          menu.state = 1;
        }
        else // Exit
        {
          menu.state = 2;
          setMusic("!");
          setFadeMode(&main_fade,FADE_IN,false);
          waitFadeDone(&main_fade);
          exit(0);
        }
      }
    }
    else if (menu.state == 1) // Bluz is on top
    {
      menu.sub_i += ctrlJustPressed(KEY_DOWN) -
                    ctrlJustPressed(KEY_UP);
      
      if (menu.mod_i == 0) // Story
      {
        if (menu.sub_i < 0) menu.sub_i = 2;
        if (menu.sub_i > 2) menu.sub_i = 0;
        
        if (ctrlJustPressed(KEY_GO))
        {
          play = 1;
          menu.state = 2;
          luaDoFile("start.lua");
          if (menu.sub_i == 0)
          {
            strncpy(lvl.next,saved_lvl,512);
          }
          if (menu.sub_i == 2)
          {
            strncpy(lvl.next,"select.lua",512);
          }
        }
        if (ctrlJustPressed(KEY_NO))
        {
          menu.state = 0;
        }
      }
      else if (menu.mod_i == 1) // Options
      {
	Config *cfg = configGet();

        if (menu.sub_i < 0) menu.sub_i = 3;
        if (menu.sub_i > 3) menu.sub_i = 0;

        if (ctrlJustPressed(KEY_LEFT))
        {
          switch (menu.sub_i)
          {
            case 0:
              cfg->music_vol -= 25;
              if (cfg->music_vol < 0) cfg->music_vol = 0;
              sprintf(text.menu.config_setting[0],"%d%%",cfg->music_vol);
            break;
            case 1:
              cfg->sound_vol -= 25;
              if (cfg->sound_vol < 0) cfg->sound_vol = 0;
              sprintf(text.menu.config_setting[1],"%d%%",cfg->sound_vol);
            break;
            case 2:
              cfg->lang_id--;
              if (cfg->lang_id < 0) cfg->lang_id = lang_n-1;
              loadLanguage();
            break;
            case 3:
              cfg->fullscreen = !cfg->fullscreen;
              strcpy(text.menu.config_setting[3],cfg->fullscreen ? text.yes : text.no);
            break;
          }
        }
        if (ctrlJustPressed(KEY_RIGHT))
        {
          switch (menu.sub_i)
          {
            case 0:
              cfg->music_vol += 25;
              if (cfg->music_vol > 100) cfg->music_vol = 100;
              sprintf(text.menu.config_setting[0],"%d%%",cfg->music_vol);
            break;
            case 1:
              cfg->sound_vol += 25;
              if (cfg->sound_vol > 100) cfg->sound_vol = 100;
              sprintf(text.menu.config_setting[1],"%d%%",cfg->sound_vol);
            break;
            case 2:
              cfg->lang_id++;
              if (cfg->lang_id >= lang_n) cfg->lang_id = 0;
              loadLanguage();
            break;
            case 3:
              cfg->fullscreen = !cfg->fullscreen;
              strcpy(text.menu.config_setting[3],cfg->fullscreen ? text.yes : text.no);
            break;
          }
        }
        if (ctrlJustPressed(KEY_NO))
        {
          menu.state = 0;
          configSave();
        }
      }
      else if (menu.mod_i == 2) // Credits
      {
        if (ctrlJustPressed(KEY_NO))
        {
          menu.state = 0;
        }
      }
    }
    
    SDL_Delay(1);
  }

  main_fade.color = WHITE;
  setFadeMode(&main_fade,FADE_IN,0);
  waitFadeDone(&main_fade);

  if (nextLevel())
  {
    setGameState(INGAME);

    setFadeMode(&main_fade,FADE_OUT,0);
    ui_fade.alpha = 0;
  }
}


int gameThread(void* p)
{
  initGameState();

  while (!exit_state)
  {
    if (checkGameState(MENU))
    {
      gameMenu();
    }
    if (checkGameState(GSQUARE))
    {
      gamegSquare();
    }
    if (checkGameState(BANNER))
    {
      gameBANNER();
    }    
    if (checkGameState(INGAME))
    {
      SDL_SemWait(logic_sem);

      gameControls();
      if (getGameState() != PAUSE)
      {
        physics(); // and player controls
      }
      if (getGameState() == INGAME)
      {
        checkBounds();
      }

      SDL_SemPost(render_sem);
    }
  }
  
  if (exit_state != EXCEPTION)
  {
    exit(0);
  }
  
  return 0;
}


void initGame()
{
  // Start game thread
  SDL_CreateThread(gameThread, "game_thread", NULL);
}

// EOF
