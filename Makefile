BIN = gsquare

OBJS = \
    main.o level.o controls.o language.o audio.o config.o lua.o\
    disp.o disp_game.o disp_ui.o\
    game.o game_physics.o\
    lib/glib2d.o

CFLAGS = $(shell sdl-config --cflags) -Wall -O2
LDFLAGS = $(shell sdl-config --libs) -lSDL_image -lGL -lpng -ljpeg -lm -llua

all: gsquare

gsquare: $(OBJS)
	gcc -o game/$(BIN) $^ $(LDFLAGS)

%.o: %.c
	gcc -o $@ -c $^ $(CFLAGS)

run: gsquare
	cd game && ./$(BIN)

clean:
	rm -f *.o $(BIN)
