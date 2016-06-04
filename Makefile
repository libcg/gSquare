BIN = gsquare
OS = $(shell uname)
CROSS ?= 

OBJS = \
    main.o level.o controls.o language.o audio.o config.o lua.o\
    disp.o disp_game.o disp_ui.o\
    game.o game_physics.o\
    lib/glib2d.o lib/glib2d_font.o

CFLAGS = $(shell sdl2-config --cflags) -Wall -O2
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf\
          -lpng -ljpeg -lm -llua

ifeq ($(OS), Darwin)
LDFLAGS += -framework OpenGL
else
LDFLAGS += -lGL
endif

all: gsquare

gsquare: $(OBJS)
	$(CROSS)gcc -o game/$(BIN) $^ $(LDFLAGS)

%.o: %.c
	$(CROSS)gcc -o $@ -c $^ $(CFLAGS)

run: gsquare
	cd game && ./$(BIN)

clean:
	rm -f *.o lib/*.o game/$(BIN)
