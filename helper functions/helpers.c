#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

char *dice_paths[] = {"grids/dice-imgs/one.png", "grids/dice-imgs/two.png", "grids/dice-imgs/three.png", "grids/dice-imgs/four.png", "grids/dice-imgs/five.png", "grids/dice-imgs/six.png"};

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
 * Function to draw a diagonal ladder between two points
 */
void draw_img(SDL_Renderer *renderer, SDL_Texture *ladder_texture, int CELL_WIDTH, int CELL_HEIGHT, int startRow, int startCol, int endRow, int endCol, int screen_x, int screen_y, double scale_x, double scale_y, int turn)
{
    // Calculate the start position in pixels (bottom of startRow, startCol)
    int startX = screen_x + startCol * CELL_WIDTH + CELL_WIDTH;
    int startY = screen_y + startRow * CELL_HEIGHT + CELL_HEIGHT / 2;

    // Calculate the end position in pixels (top of endRow, endCol)
    int endX = screen_x + endCol * CELL_WIDTH + CELL_WIDTH;
    int endY = screen_y + endRow * CELL_HEIGHT + CELL_HEIGHT / 2;

    // Calculate the width (distance btw columns) and height (distance between columns)
    int ladderWidth = scale_x * abs(endX - startX);
    int ladderHeight = scale_y * abs(endY - startY);

    // Calculate the angle of rotation (in radians) using the arctangent of slope
    double angle = atan2(endY - startY, endX - startX) * turn / M_PI;

    // Create the rectangle for the ladder image
    SDL_Rect ladderRect = {startX, startY, ladderWidth, ladderHeight};

    // Render the ladder texture, rotated to match diagonal
    SDL_RenderCopyEx(renderer, ladder_texture, NULL, &ladderRect, angle, NULL, SDL_FLIP_NONE);
    // SDL_RenderCopy(renderer, ladder_texture, NULL, &ladderRect);
} // draw_diagonal_ladder
