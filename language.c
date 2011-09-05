// 
// gSquare by Geecko
//
// This work is licensed under the Creative Commons BY-NC-SA 3.0 Unported License.
// See LICENSE for more details.

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "language.h"

Text text;

void initLanguage()
{
  // Menu
  strcpy(text.menu.title[0],"Story");
  strcpy(text.menu.title[1],"Options");
  strcpy(text.menu.title[2],"Credits");
  strcpy(text.menu.title[3],"Exit");
  strcpy(text.menu.story[0],"Continue story !");
  strcpy(text.menu.story[1],"Restart from the beginning.");
  strcpy(text.menu.config[0],"Music volume : ");
  strcpy(text.menu.config[1],"Sound volume : ");
  sprintf(text.menu.config_setting[0],"%d%%",cfg.music_vol);
  sprintf(text.menu.config_setting[1],"%d%%",cfg.sound_vol);
  // Pause 
  strcpy(text.pause.title,"Pause.");
  strcpy(text.pause.choice[0],"Resume");
  strcpy(text.pause.choice[1],"Respawn");
  strcpy(text.pause.choice[2],"Restart");
  // Credits
  strcpy(text.credits,
"gSquare\n\nBy meastnt and Geecko\nDesign by Maxime Brugnon and CaptainKill\nMu\
sic by c418 (mainly from Little Things)\nTesting by Léo, Arthur, Baptiste, Maxi\
me\n\nUsing :\nGraphics library - gLib2D by Geecko\nFont library - intraFont-G \
by BenHur\nAudio library - aalib by Arshia001\nPSPSDK - ps2dev.org\n\nThanks to\
:\nFrench PSP community (PSP-Gen, XtreamLua)\nSony for his marvellous developme\
nt platform"); 
}
  

// EOF
