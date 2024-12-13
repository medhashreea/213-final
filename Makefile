CC := clang
CFLAGS := -g -fsanitize=address `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm
TARGETS := window 

all: $(TARGETS)

clean:
	rm -f $(TARGETS) /tmp/window-e6827.o

window: window.c
	@echo Compiling $<
	$(CC) helpers/helpers.c -o window window.c $(CFLAGS) $<
	@echo