BIN = gsquare

OBJS = \
    main.o level.o controls.o language.o audio.o config.o lua.o\
    disp.o disp_game.o disp_ui.o\
    game.o game_physics.o\
    lib/glib2d.o

CFLAGS = -Wall -02
LDFLAGS = -lSDL -lSDL_image -lSDL_ttf -lGL -lpng -ljpeg -lm -llua

all: gsquare

gsquare: $(OBJS)
	gcc -o game/$(BIN) $^ $(LDFLAGS)

%.o: %.c
	gcc -o $@ -c $^

run: gsquare
	cd game && ./$(BIN)

clean:
	rm -f *.o $(BIN)
