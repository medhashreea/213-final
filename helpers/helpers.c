#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "helpers.h"

// array of paths
char *dice_paths[] = {"grids/dice-imgs/one.png", "grids/dice-imgs/two.png", "grids/dice-imgs/three.png", "grids/dice-imgs/four.png", "grids/dice-imgs/five.png", "grids/dice-imgs/six.png"};
char *player_imgs[] = {"grids/images/character.png", "grids/images/character2.png", "grids/images/character3.png", "grids/images/character4.png"};

void draw_dice(SDL_Renderer *renderer, SDL_Texture *dice_texture)
{
    if (dice_texture == NULL)
    {
        return; // Do nothing if there is no dice texture
    }

    // Create the rectangle for the dice image
    SDL_Rect dice_rect = {25, 25, 175, 175};
    SDL_RenderCopy(renderer, dice_texture, NULL, &dice_rect);
}

/**
 * Function to draw a diagonal  between two points
 */
void draw_img(SDL_Renderer *renderer, SDL_Texture *texture, int CELL_WIDTH, int CELL_HEIGHT, int startRow, int startCol, int endRow, int endCol, int screen_x, int screen_y, double scale_x, double scale_y, int turn)
{
    // Calculate the start position in pixels (bottom of startRow, startCol)
    int startX = screen_x + startCol * CELL_WIDTH + CELL_WIDTH;
    int startY = screen_y + startRow * CELL_HEIGHT + CELL_HEIGHT / 2;

    // Calculate the end position in pixels (top of endRow, endCol)
    int endX = screen_x + endCol * CELL_WIDTH + CELL_WIDTH;
    int endY = screen_y + endRow * CELL_HEIGHT + CELL_HEIGHT / 2;

    // Calculate the width (distance btw columns) and height (distance between columns)
    int width = scale_x * abs(endX - startX);
    int height = scale_y * abs(endY - startY);

    // Calculate the angle of rotation (in radians) using the arctangent of slope
    double angle = atan2(endY - startY, endX - startX) * turn / M_PI;

    // Create the rectangle for the  image
    SDL_Rect rect = {startX, startY, width, height};

    // Render the  texture, rotated to match diagonal
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
} // draw_diagonal_


/**
 * Returns the new snake or ladder position for any given arrays.
 *
 * \param current_pos - an integer representing the current position
 * \param ladders - a 2D array containing ladder positions
 * \param num_ladders - the number of ladders in the grid
 * \param snakes - a 2D array containing snake positions
 * \param num_snakes - the number of snakes in the grid
 * \return current_pos - an integer representing the updated current position
 */
int snake_ladder_pos(int current_pos, int ladders[][2], int num_ladders, int snakes[][2], int num_snakes)
{
    // Check for snakes
    for (int i = 0; i < num_snakes; i++)
    {
        if (current_pos == snakes[i][0])
        {
            current_pos = snakes[i][1];
            break;
        }
    }

    // Check for ladders
    for (int i = 0; i < num_ladders; i++)
    {
        if (current_pos == ladders[i][0])
        {
            current_pos = ladders[i][1];
            break;
        }
    }

    return current_pos;
}

/**
 * Determines if the position is a snake or ladder for any given arrays.
 *
 * \param current_pos - an integer representing the current position
 * \param ladders - a 2D array containing ladder positions
 * \param num_ladders - the number of ladders in the grid
 * \param snakes - a 2D array containing snake positions
 * \param num_snakes - the number of snakes in the grid
 * \return bool - returns true if the position is a snake or ladder, false otherwise
 */
bool snake_or_ladder(int current_pos, int ladders[][2], int num_ladders, int snakes[][2], int num_snakes)
{
    for (int i = 0; i < num_snakes; i++)
    {
        if (current_pos == snakes[i][0])
        {
            return true;
        }
    }

    for (int i = 0; i < num_ladders; i++)
    {
        if (current_pos == ladders[i][0])
        {
            return true;
        }
    }

    return false;
}

/**
 * Moves the current player
 *
 * \param renderer - a pointer to the renderer
 * \param current_pos - an integer representing the current position
 * \param player_texture - a pointer to the player_texture
 */

void move_player(SDL_Renderer *renderer, int current_pos, SDL_Texture *player_texture, int SCREEN_WIDTH, int SCREEN_HEIGHT, int CELL_WIDTH, int CELL_HEIGHT)
{
    // Board dimensions
    int rows = 25;
    int cols = 5;
    int cell_width = CELL_WIDTH;
    int cell_height = CELL_HEIGHT;

    // Calculate board position
    int screen_x = (SCREEN_WIDTH - (cols * cell_width)) / 2;   // Center horizontally
    int screen_y = (SCREEN_HEIGHT - (rows * cell_height)) / 2; // Center vertically

    // Calculate the character's grid position
    int row = current_pos / cols;
    int col;

    // If the row is even, increment the character (move right)
    if (row % 2 == 0)
    {
        col = current_pos % cols;
    }
    // If the row is odd, decrement character (move left)
    else
    {
        col = cols - 1 - (current_pos % cols);
    }

    // Calculate the character's position
    int char_x = screen_x + col * cell_width;
    int char_y = screen_y + (rows - 1 - row) * cell_height; // Top-to-bottom layout

    // Render the character
    SDL_Rect character_rect = {char_x, char_y, cell_width, cell_height};
    SDL_RenderCopy(renderer, player_texture, NULL, &character_rect);
    IMG_Quit();
}