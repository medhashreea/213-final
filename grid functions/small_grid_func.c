#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>
#include <stdbool.h>
#include "../helpers/helpers.h"

// __syncthreads_count(count)

/*
 * Ladder positions on the grid
 */
int ladders[3][2] = {{25, 34}, {63, 74}, {98, 107}};

/*
 * Snake positions on the grid
 */

int snakes[3][2] = {{28, 10}, {62, 43}, {119, 88}};

// Global variables
int dice_value;

/*
 * Returns new position
 */
int snake_ladder_pos(int cur_pos)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks if it's a snake
        if (cur_pos == snakes[i][0])
        {
            return snakes[i][1];
        }
        // Checks if it's a ladder
        else if (cur_pos == ladders[i][0])
        {
            return ladders[i][1];
        }
    }
    return cur_pos;
}

/*
 * Checks if it's a snake or ladder
 */
bool snake_or_ladder(int cur_pos)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks if it's a snake
        return (cur_pos == snakes[i][0] || cur_pos == ladders[i][0]);
    }
    return false;
}

void move_player(int cur_pos)
{
    if (snake_or_ladder(cur_pos))
    {
        snake_ladder_pos(cur_pos);
    }
    else
    {
        cur_pos += dice_value;
    }
}

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
    // int x = GRID_OFFSET_X + col * SMALL_CELL_WIDTH;
    // int y = GRID_OFFSET_Y + row * SMALL_CELL_HEIGHT;
    int x = col * SMALL_CELL_WIDTH;
    int y = row * SMALL_CELL_HEIGHT;

    // Define the destination rectangle for the player sprite
    SDL_Rect destRect = {x, y, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT};

    // Render the player texture
    SDL_RenderCopy(renderer, playerTexture, NULL, &destRect);
}