
CC := clang
CFLAGS := -g `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm
TARGETS := window

all: $(TARGETS)

clean:
	rm -f $(TARGETS) *.o

window: window.c helpers/helpers.c
	@echo Compiling $@
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Build complete: $@"

zip:
	@echo "Generating window.zip file to submit to Gradescope..."
	@zip -q -r window.zip . -x .git/\* .vscode/\* .clang-format .gitignore window
	@echo "Done. Please upload window.zip to Gradescope."