MEDIA = /media/PANDORA/PSP/GAME/CAT_Homebrews\ perso/
TARGET = gSquare

OBJS = main.o level.o controls.o language.o audio.o config.o\
       disp.o disp_game.o disp_ui.o\
       game.o game_physics.o\
       lua.o\
       ./lib/intraFont.o ./lib/libccc.o\
       ./lib/glib2d.o\
       ./lib/pspaalib.o ./lib/pspaalibat3.o ./lib/pspaalibeffects.o\
       ./lib/pspaalibogg.o ./lib/pspaalibscemp3.o ./lib/pspaalibwav.o
LIBS = -lpng -ljpeg -lz -lpspgum -lpspgu -lpsprtc -lpspvram -llua\
       -lpspaudio -lpspaudiocodec -lpspatrac3 -lpspmp3 -lvorbisfile -lvorbis\
       -logg -lpsppower -lm -lpspusb -lpspusbstor

CFLAGS = -O2 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSP_FW_VERSION = 500
BUILD_PRX = 0
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = gSquare 1.1pre
PSP_EBOOT_ICON = icon0.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak 
install:
	cp ./EBOOT.PBP $(MEDIA)$(TARGET)
dir:
	mkdir $(MEDIA)$(TARGET)
lclean:
	rm *.o
