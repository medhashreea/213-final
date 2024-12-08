CC = clang
CFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lm

# Source files and object files
SRC = window.c helpers/helpers.c 
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = window

# Default rule (build the program)
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

# Rule to compile .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)
