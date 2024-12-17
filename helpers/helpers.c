#include <stdio.h>
#include <time.h>
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
 * Returns the new snake or ladder position
 *
 * \param current_pos - an integer representing the current position
 * \return current_pos - an integer representing the updated current position
 */
int snake_ladder_pos(int current_pos, int ladder, int snake)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks if it's a snake
        if (current_pos == snake[i][0])
        {
            current_pos = snake[i][1];
            break;
        }
        // Checks if it's a ladder
        else if (current_pos == ladder[i][0])
        {
            current_pos = ladder[i][1];
            break;
        }
    }
    return current_pos;
}

/**
 * Detrmines if the position is a snake or ladder
 *
 * \param current_pos - an integer representing the current position
 * \return bool
 */
bool snake_or_ladder(int current_pos, int ladder, int snake)
{
    for (int i = 0; i < 3; i++)
    {
        if (current_pos == snake[i][0] || current_pos == ladder[i][0])
        {
            return true;
        }
    }
    return false;
}
