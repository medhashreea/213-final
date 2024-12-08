#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>
#include "../helpers/helpers.h"

// #define SCREEN_WIDTH 1000  // Width of screen
// #define SCREEN_HEIGHT 1000 // Height of screen
#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1000
#define MED_CELL_WIDTH 50  // Width of each cell
#define MED_CELL_HEIGHT 25 // Height of each cell

// __syncthreads_count(count)

// Global variables
int dice_value;

/*
 * Ladder positions on the grid
 */
int medium_ladders[3][2] = {{25, 34}, {63, 74}, {98, 107}};

/*
 * Snake positions on the grid
 */
int medium_snakes[3][2] = {{28, 10}, {62, 43}, {119, 88}};

/**
 * Renders the player at a given grid position.
 *
 * @param renderer The SDL renderer.
 * @param row The player's row on the grid.
 * @param col The player's column on the grid.
 * @param playerTexture The player's texture (image or sprite).
 */
void renderPlayer(SDL_Renderer *renderer, int row, int col, SDL_Texture *playerTexture)
{

    // Screen offsets for the grid (if grid isn't at (0, 0))
    // const int GRID_OFFSET_X = 25;
    // const int GRID_OFFSET_Y = 50;

    // Calculate screen coordinates
    // int x = GRID_OFFSET_X + col * MED_CELL_WIDTH;
    // int y = GRID_OFFSET_Y + row * MED_CELL_HEIGHT;
    int x = col * MED_CELL_WIDTH;
    int y = row * MED_CELL_HEIGHT;

    // Define the destination rectangle for the player sprite
    SDL_Rect destRect = {x, y, MED_CELL_WIDTH, MED_CELL_HEIGHT};

    // Render the player texture
    SDL_RenderCopy(renderer, playerTexture, NULL, &destRect);
}