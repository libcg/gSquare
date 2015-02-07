BIN = gsquare

OBJS = \
    main.o level.o controls.o language.o audio.o config.o lua.o\
    disp.o disp_game.o disp_ui.o\
    game.o game_physics.o\
    lib/glib2d.o

CFLAGS = $(shell sdl2-config --cflags) -Wall -O2
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -lGL -lpng -ljpeg -lm -llua

all: gsquare

gsquare: $(OBJS)
	gcc -o game/$(BIN) $^ $(LDFLAGS)

%.o: %.c
	gcc -o $@ -c $^ $(CFLAGS)

run: gsquare
	cd game && ./$(BIN)

clean:
	rm -f *.o $(BIN)
