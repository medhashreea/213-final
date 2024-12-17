/*
 * medium_grid.c
 * The snakes and ladders game on a medium grid.
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>
#include <stdbool.h>
#include <time.h>
#include "../helpers/helpers.h"

#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1000
#define MED_CELL_WIDTH 50  // Width of each cell
#define MED_CELL_HEIGHT 25 // Height of each cell
#define MED_FINAL_POS 599  // final cell

// Ladder positions on the grid
int medium_ladders[4][2] = {{74, 103}, {174, 203}, {379, 410}, {477, 506}};

// Snake positions on the grid
int medium_snakes[4][2] = {{243, 123}, {288, 225}, {354, 323}, {574, 516}};

/**
 * Initializes the grid
 *
 * \param renderer - a pointer to the renderer
 * \param screen_x - in integer representign the x coordinate
 * \param screen_y - in integer representign the y coordinate
 */
void place_medium_imgs(SDL_Renderer *renderer, int screen_x, int screen_y)
{
    // Init all ladders (SDL_Surface)
    SDL_Surface *ladder = IMG_Load("grids/images/ladder.png");   // Load your PNG image
    SDL_Surface *ladder2 = IMG_Load("grids/images/ladder2.png"); // Load your PNG image
    SDL_Surface *ladder3 = IMG_Load("grids/images/ladder3.png"); // Load your PNG image
    SDL_Surface *ladder4 = IMG_Load("grids/images/ladder4.png"); // Load your PNG image

    SDL_Surface *snake = IMG_Load("grids/images/snake2.png");  // Load your PNG image
    SDL_Surface *snake2 = IMG_Load("grids/images/snake5.png"); // Load your PNG image
    SDL_Surface *snake3 = IMG_Load("grids/images/snake6.png"); // Load your PNG image
    SDL_Surface *snake4 = IMG_Load("grids/images/snake8.png"); // Load your PNG image

    if (ladder == NULL || ladder2 == NULL || ladder3 == NULL || ladder4 == NULL)
    {
        printf("Failed to load ladder image: %s\n", IMG_GetError());
        return;
    }

    if (snake == NULL || snake2 == NULL || snake3 == NULL || snake4 == NULL)
    {
        printf("Failed to load snake image: %s\n", IMG_GetError());
        return;
    }

    // Init all ladders (SDL_Texture)
    SDL_Texture *ladder_texture = SDL_CreateTextureFromSurface(renderer, ladder);
    SDL_Texture *ladder_texture2 = SDL_CreateTextureFromSurface(renderer, ladder2);
    SDL_Texture *ladder_texture3 = SDL_CreateTextureFromSurface(renderer, ladder3);
    SDL_Texture *ladder_texture4 = SDL_CreateTextureFromSurface(renderer, ladder4);

    // Init all snakes (SDL_Texture)
    SDL_Texture *snake_texture = SDL_CreateTextureFromSurface(renderer, snake);
    SDL_Texture *snake_texture2 = SDL_CreateTextureFromSurface(renderer, snake2);
    SDL_Texture *snake_texture3 = SDL_CreateTextureFromSurface(renderer, snake3);
    SDL_Texture *snake_texture4 = SDL_CreateTextureFromSurface(renderer, snake4);

    // Free all ladder Surface
    SDL_FreeSurface(ladder);
    SDL_FreeSurface(ladder2);
    SDL_FreeSurface(ladder3);
    SDL_FreeSurface(ladder4);

    // Free all the snakes
    SDL_FreeSurface(snake);
    SDL_FreeSurface(snake2);
    SDL_FreeSurface(snake3);
    SDL_FreeSurface(snake4);

    // Checks if any of the ladder textures are null
    if (ladder_texture == NULL || ladder_texture2 == NULL || ladder_texture3 == NULL || ladder_texture4 == NULL) // failure check
    {
        printf("Failed to create ladder texture: %s\n", SDL_GetError());
        return;
    }

    // Checcks if any of the snake textures are null
    if (snake_texture == NULL || snake_texture2 == NULL || snake_texture3 == NULL || snake_texture4 == NULL) // failure check
    {
        printf("Failed to create snake texture: %s\n", SDL_GetError());
        return;
    }

    // Places images on the grid
    draw_img(renderer, ladder_texture, MED_CELL_WIDTH, MED_CELL_HEIGHT, 6, 1, 8, 3, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, ladder_texture3, MED_CELL_WIDTH, MED_CELL_HEIGHT, 26, 4, 28, 6, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture2, MED_CELL_WIDTH, MED_CELL_HEIGHT, 33, 12, 35, 14, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture4, MED_CELL_WIDTH, MED_CELL_HEIGHT, 12, 8, 14, 10, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, snake_texture, MED_CELL_WIDTH, MED_CELL_HEIGHT, 24, 0, 30, 4, screen_x, screen_y, 1, 1, 270);
    draw_img(renderer, snake_texture2, MED_CELL_WIDTH, MED_CELL_HEIGHT, 14, 4, 18, 8, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, snake_texture3, MED_CELL_WIDTH, MED_CELL_HEIGHT, 1, 2, 5, 6, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, snake_texture4, MED_CELL_WIDTH, MED_CELL_HEIGHT, 20, 10, 24, 14, screen_x, screen_y, 1, 1, 0);

    // Free the image texture after rendering
    SDL_DestroyTexture(ladder_texture);
    SDL_DestroyTexture(ladder_texture2);
    SDL_DestroyTexture(ladder_texture3);
    SDL_DestroyTexture(ladder_texture4);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snake_texture2);
    SDL_DestroyTexture(snake_texture3);
    SDL_DestroyTexture(snake_texture4);
}

/*
 * Creates the grid on the window and call image placement function
 */
void medium_grid(SDL_Renderer *renderer, TTF_Font *font)
{
    int margin = 25; // margin size
    int rows = 40;
    int cols = 15;

    // calculate board dimensions
    int width = (cols * MED_CELL_WIDTH);   // 5 cells horizontally
    int height = (rows * MED_CELL_HEIGHT); // 25 rows vertically

    // calculate board position
    int screen_x = (SCREEN_WIDTH - width) / 2;   // Center horizontally
    int screen_y = (SCREEN_HEIGHT - height) / 2; // Center vertically

    // render board
    SDL_Rect board = {screen_x, screen_y, width, height}; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 214, 151, 213, 1);   // Set color to pinnk
    SDL_RenderFillRect(renderer, &board);                 // Fill the rectangle

    // Set the color for the grid lines (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

    for (int x = screen_x; x <= screen_x + width; x += MED_CELL_WIDTH)
    {
        SDL_RenderDrawLine(renderer, x, screen_y, x, screen_y + height);
    } // for loop to draw the vertical grid lines

    for (int y = screen_y; y <= screen_y + height; y += MED_CELL_HEIGHT)
    {
        SDL_RenderDrawLine(renderer, screen_x, y, screen_x + width, y);
    } // for loop to draw the horizontal grid lines

    SDL_Color color = {255, 255, 255, 255}; // color
    int number = 1;                         // start value
    char num_str[10];

    // loop to add values in each cell
    for (int row = rows - 1; (row <= rows) && (row >= 0); row--) // loop over all rows first
    {
        if ((row % 2) != 0) // check if row is even
        {
            for (int col = 0; col < cols; col++) // for columns going left to right, increment
            {
                snprintf(num_str, sizeof(num_str), "%d", number++); // print value in cell

                // Create text surface and texture
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, num_str, color);
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
                int cellX = screen_x + col * MED_CELL_WIDTH;
                int cellY = screen_y + row * MED_CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (MED_CELL_WIDTH - textSurface->w) / 2,
                    cellY + (MED_CELL_HEIGHT - textSurface->h) / 2,
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
                snprintf(num_str, sizeof(num_str), "%d", number++); // print value in cell

                // Create text surface and texture
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, num_str, color);
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
                int cellX = screen_x + col * MED_CELL_WIDTH;
                int cellY = screen_y + row * MED_CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (MED_CELL_WIDTH - textSurface->w) / 2,
                    cellY + (MED_CELL_HEIGHT - textSurface->h) / 2,
                    textSurface->w,
                    textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            } // column loop
        } // cond check for odd/even rows
    } // row loop

    // call to function that places all snakes and ladders on grid (hard coded)
    place_medium_imgs(renderer, screen_x, screen_y);
} // medium_grid

void medium_grid_game(SDL_Renderer *renderer, TTF_Font *font, int num_players)
{
    srand(time(NULL));      // init to generate random values later
    IMG_Init(IMG_INIT_PNG); // Initialize support for PNGs

    // Main loop flag
    int quit = 0;
    SDL_Event e;
    SDL_Texture *dice_texture = NULL; // Variable to hold the current dice texture

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
        medium_grid(renderer, font);
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