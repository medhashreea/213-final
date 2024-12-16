#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>
#include "../helpers/helpers.h"

#define SCREEN_WIDTH 1900    // Width of screen
#define SCREEN_HEIGHT 1000   // Height of screen
#define LARGE_CELL_WIDTH 37  // Width of each cell
#define LARGE_CELL_HEIGHT 23 // Height of each cell

// /**
//  * Function to draw a diagonal ladder between two points
//  */
// void draw_img(SDL_Renderer *renderer, SDL_Texture *ladder_texture, int startRow, int startCol, int endRow, int endCol, int screen_x, int screen_y, double scale_x, double scale_y, int turn)
// {
//     // Calculate the start position in pixels (bottom of startRow, startCol)
//     int startX = screen_x + startCol * CELL_WIDTH + CELL_WIDTH;
//     int startY = screen_y + startRow * CELL_HEIGHT + CELL_HEIGHT / 2;

//     // Calculate the end position in pixels (top of endRow, endCol)
//     int endX = screen_x + endCol * CELL_WIDTH + CELL_WIDTH;
//     int endY = screen_y + endRow * CELL_HEIGHT + CELL_HEIGHT / 2;

//     // Calculate the width (distance btw columns) and height (distance between columns)
//     int ladderWidth = scale_x * abs(endX - startX);
//     int ladderHeight = scale_y * abs(endY - startY);

//     // Calculate the angle of rotation (in radians) using the arctangent of slope
//     double angle = atan2(endY - startY, endX - startX) * turn / M_PI;

//     // Create the rectangle for the ladder image
//     SDL_Rect ladderRect = {startX, startY, ladderWidth, ladderHeight};

//     // Render the ladder texture, rotated to match diagonal
//     SDL_RenderCopyEx(renderer, ladder_texture, NULL, &ladderRect, angle, NULL, SDL_FLIP_NONE);
//     // SDL_RenderCopy(renderer, ladder_texture, NULL, &ladderRect);
// } // draw_diagonal_ladder

/**
 * Places the Snakes and Ladders images
 */
void place_large_imgs(SDL_Renderer *renderer, int screen_x, int screen_y)
{
    IMG_Init(IMG_INIT_PNG); // Initialize support for PNGs
    char *dice_choice = "";

    int dice_value = rand() % 6;
    dice_choice = dice_paths[dice_value];

    // Init all ladders (SDL_Surface)
    SDL_Surface *ladder = IMG_Load("grids/images/ladder.png");   // Load your PNG image
    SDL_Surface *ladder2 = IMG_Load("grids/images/ladder2.png"); // Load your PNG image
    SDL_Surface *ladder3 = IMG_Load("grids/images/ladder3.png"); // Load your PNG image
    SDL_Surface *ladder4 = IMG_Load("grids/images/ladder4.png"); // Load your PNG image
    SDL_Surface *ladder5 = IMG_Load("grids/images/ladder5.png"); // Load your PNG image

    SDL_Surface *snake = IMG_Load("grids/images/snake1.png");  // Load your PNG image
    SDL_Surface *snake2 = IMG_Load("grids/images/snake2.png"); // Load your PNG image
    SDL_Surface *snake3 = IMG_Load("grids/images/snake3.png"); // Load your PNG image
    SDL_Surface *snake4 = IMG_Load("grids/images/snake4.png"); // Load your PNG image
    SDL_Surface *snake5 = IMG_Load("grids/images/snake6.png"); // Load your PNG image

    if (ladder == NULL || ladder2 == NULL || ladder3 == NULL || ladder4 == NULL || ladder5 == NULL)
    {
        printf("Failed to load ladder image: %s\n", IMG_GetError());
        return;
    }

    if (snake == NULL || snake2 == NULL || snake3 == NULL || snake4 == NULL || snake5 == NULL)
    {
        printf("Failed to load snake image: %s\n", IMG_GetError());
        return;
    }

    // Init all ladders (SDL_Texture)
    SDL_Texture *ladder_texture = SDL_CreateTextureFromSurface(renderer, ladder);
    SDL_Texture *ladder_texture2 = SDL_CreateTextureFromSurface(renderer, ladder2);
    SDL_Texture *ladder_texture3 = SDL_CreateTextureFromSurface(renderer, ladder3);
    SDL_Texture *ladder_texture4 = SDL_CreateTextureFromSurface(renderer, ladder4);
    SDL_Texture *ladder_texture5 = SDL_CreateTextureFromSurface(renderer, ladder5);

    // Init all snakes (SDL_Texture)
    SDL_Texture *snake_texture = SDL_CreateTextureFromSurface(renderer, snake);
    SDL_Texture *snake_texture2 = SDL_CreateTextureFromSurface(renderer, snake2);
    SDL_Texture *snake_texture3 = SDL_CreateTextureFromSurface(renderer, snake3);
    SDL_Texture *snake_texture4 = SDL_CreateTextureFromSurface(renderer, snake4);
    SDL_Texture *snake_texture5 = SDL_CreateTextureFromSurface(renderer, snake5);


    // Free all ladder Surface
    SDL_FreeSurface(ladder); // Free the surface after creating texture
    SDL_FreeSurface(ladder2);
    SDL_FreeSurface(ladder3);
    SDL_FreeSurface(ladder4);
    SDL_FreeSurface(ladder5);

    // Free all the snakes
    SDL_FreeSurface(snake);
    SDL_FreeSurface(snake2);
    SDL_FreeSurface(snake3);
    SDL_FreeSurface(snake4);
    SDL_FreeSurface(snake5);

    if (ladder_texture == NULL || ladder_texture2 == NULL || ladder_texture3 == NULL || ladder_texture4 == NULL) //|| ladder_texture5 == NULL) // failure check
    {
        printf("Failed to create ladder texture: %s\n", SDL_GetError());
        return;
    }

    if (snake_texture == NULL || snake_texture2 == NULL || snake_texture3 == NULL || snake_texture4 == NULL) //|| snake_texture5 == NULL) // failure check
    {
        printf("Failed to create snake texture: %s\n", SDL_GetError());
        return;
    }

    // place ladder
    draw_img(renderer, ladder_texture, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 18, 1, 20, 3, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, ladder_texture3, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 26, 4, 28, 6, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture2, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 33, 12, 35, 14, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture4, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 12, 8, 14, 10, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture5, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 4, 10, 6, 12, screen_x, screen_y, 1, 1, 0);

    // place snakes
    draw_img(renderer, snake_texture, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 30, 0, 34, 4, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, snake_texture2, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 14, 4, 18, 8, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, snake_texture3, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 1, 2, 5, 6, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, snake_texture4, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 20, 10, 24, 14, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, snake_texture5, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 6, 8, 9, 11, screen_x, screen_y, 1, 1, 0);

    // Free the image texture after rendering
    SDL_DestroyTexture(ladder_texture);
    SDL_DestroyTexture(ladder_texture2);
    SDL_DestroyTexture(ladder_texture3);
    SDL_DestroyTexture(ladder_texture4);
    SDL_DestroyTexture(ladder_texture5);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snake_texture2);
    SDL_DestroyTexture(snake_texture3);
    SDL_DestroyTexture(snake_texture4);
    SDL_DestroyTexture(snake_texture5);
}

/*
 * Creates the grid on the window and call image placement function
 */
void large_grid(SDL_Renderer *renderer, TTF_Font *font)
{
    int margin = 25; // margin size
    int rows = 40;
    int cols = 15;

    // calculate board dimensions
    int width = (cols * LARGE_CELL_WIDTH);   // 5 cells horizontally
    int height = (rows * LARGE_CELL_HEIGHT); // 25 rows vertically

    // calculate board position
    int screen_x = (SCREEN_WIDTH - width) / 2;   // Center horizontally
    int screen_y = (SCREEN_HEIGHT - height) / 2; // Center vertically

    // render board
    SDL_Rect board = {screen_x, screen_y, width, height}; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 214, 151, 213, 1);   // Set color to pinnk
    SDL_RenderFillRect(renderer, &board);                 // Fill the rectangle

    // Set the color for the grid lines (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

    for (int x = screen_x; x <= screen_x + width; x += LARGE_CELL_WIDTH)
    {
        SDL_RenderDrawLine(renderer, x, screen_y, x, screen_y + height);
    } // vertical lines on board

    for (int y = screen_y; y <= screen_y + height; y += LARGE_CELL_HEIGHT)
    {
        SDL_RenderDrawLine(renderer, screen_x, y, screen_x + width, y);
    } // horizontal lines on board

    // add values in boxes
    SDL_Color color = {255, 255, 255, 255};
    int number = 1;
    char numStr[10];

    // loop to add values in each cell
    for (int row = rows - 1; (row <= rows) && (row >= 0); row--) // loop over all rows first
    {
        if ((row % 2) == 0) // check if row is even
        {
            for (int col = 0; col < cols; col++) // for columns going left to right, increment
            {
                snprintf(numStr, sizeof(numStr), "%d", number++); // print value in cell

                // Create text surface and texture
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, numStr, color);
                if (!textSurface)
                {
                    printf("Failed to render text: %s\n", TTF_GetError());
                    continue;
                }

                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (!textTexture)
                {
                    printf("Failed to create texture: %s\n", SDL_GetError());
                    SDL_FreeSurface(textSurface);
                    continue;
                }
                // Calculate text position (centered in the cell)
                int cellX = screen_x + col * LARGE_CELL_WIDTH;
                int cellY = screen_y + row * LARGE_CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (LARGE_CELL_WIDTH - textSurface->w) / 2,
                    cellY + (LARGE_CELL_HEIGHT - textSurface->h) / 2,
                    textSurface->w,
                    textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }
        else
        {
            for (int col = cols - 1; (col <= cols) && (col >= 0); col--) // for columns going right to left , decrement
            {
                snprintf(numStr, sizeof(numStr), "%d", number++); // print value in cell

                // Create text surface and texture
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, numStr, color);
                if (!textSurface)
                {
                    printf("Failed to render text: %s\n", TTF_GetError());
                    continue;
                }

                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                if (!textTexture)
                {
                    printf("Failed to create texture: %s\n", SDL_GetError());
                    SDL_FreeSurface(textSurface);
                    continue;
                }

                // Calculate text position (centered in the cell)
                int cellX = screen_x + col * LARGE_CELL_WIDTH;
                int cellY = screen_y + row * LARGE_CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (LARGE_CELL_WIDTH - textSurface->w) / 2,
                    cellY + (LARGE_CELL_HEIGHT - textSurface->h) / 2,
                    textSurface->w,
                    textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            } // column loop
        } // cond check for odd/even rows
    } // row loop

    // call to function that places all snakes and ladders on grid (hard coded)
    place_large_imgs(renderer, screen_x, screen_y);
} // large_grid

void large_grid_game(SDL_Renderer *renderer, TTF_Font *font, int num_players)
{
    // Main loop flag
    int quit = 0;
    SDL_Event e;

    // Variable to hold the current dice texture
    SDL_Texture *dice_texture = NULL;

    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                // Check if left mouse button was clicked
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    // Generate a random dice value and choose the corresponding texture
                    printf("num players = %d\n", num_players);
                    int dice_value = rand() % 6;
                    char *dice_choice = dice_paths[dice_value];

                    // Load the new dice texture
                    SDL_Surface *dice_surface = IMG_Load(dice_choice);
                    if (dice_surface == NULL)
                    {
                        printf("Failed to load dice image: %s\n", IMG_GetError());
                    }
                    else
                    {
                        // Create the texture from the loaded surface
                        if (dice_texture != NULL)
                        {
                            SDL_DestroyTexture(dice_texture); // Clean up the previous texture
                        }
                        dice_texture = SDL_CreateTextureFromSurface(renderer, dice_surface);
                        SDL_FreeSurface(dice_surface); // Free the surface after creating texture
                    }
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Draw the grid
        large_grid(renderer, font);
        draw_dice(renderer, dice_texture);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // // Clean up and quit SDL
    // // Clean up and quit SDL
    // if (dice_texture != NULL)
    // {
    //     SDL_DestroyTexture(dice_texture); // Free the texture when quitting
    // }
    // TTF_CloseFont(font);
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // // SDL_DestroyTexture(currentImage);
    // TTF_Quit();
    // SDL_Quit();

    // return 0;
}