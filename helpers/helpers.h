#include <SDL2/SDL.h>

// Array of dice paths
extern char *dice_paths[]; // Declare as external to avoid redefinition errors

// Function to draw the dice
void draw_dice(SDL_Renderer *renderer, SDL_Texture *dice_texture);

// Function to draw a diagonal ladder between two points
void draw_img(SDL_Renderer *renderer, SDL_Texture *ladder_texture, int CELL_WIDTH, int CELL_HEIGHT, int startRow, int startCol, int endRow, int endCol, int screen_x, int screen_y, double scale_x, double scale_y, int turn);