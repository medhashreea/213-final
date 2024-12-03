#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>

#include "../helpers/dice.c"

#define SCREEN_WIDTH 1000  // Width of screen
#define SCREEN_HEIGHT 1000 // Height of screen
#define CELL_WIDTH 50     // Width of each cell
#define CELL_HEIGHT 25    // Height of each cell

/**
 * Function to draw a diagonal ladder between two points
 */
void draw_img(SDL_Renderer *renderer, SDL_Texture *ladder_texture, int startRow, int startCol, int endRow, int endCol, int screen_x, int screen_y, double scale_x, double scale_y, int turn)
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

/**
 * Places the Snakes and Ladders images
 */
void place_imgs(SDL_Renderer *renderer, int screen_x, int screen_y) {
    IMG_Init(IMG_INIT_PNG); // Initialize support for PNGs
    char *dice_choice = "";

    int dice_value = rand() % 6;
    dice_choice = dice_paths[dice_value];

    // // // init dice
    // char* dice_chose = roll_dice(renderer);
    // SDL_Surface *dice = IMG_Load(dice_choice); // Load your PNG image

    // Init all ladders (SDL_Surface)
    SDL_Surface *ladder = IMG_Load("grids/images/ladder.png");   // Load your PNG image
    SDL_Surface *ladder2 = IMG_Load("grids/images/ladder2.png"); // Load your PNG image
    SDL_Surface *ladder3 = IMG_Load("grids/images/ladder3.png"); // Load your PNG image
    SDL_Surface *ladder4 = IMG_Load("grids/images/ladder4.png"); // Load your PNG image

    SDL_Surface *snake = IMG_Load("grids/images/snake2.png");  // Load your PNG image
    SDL_Surface *snake2 = IMG_Load("grids/images/snake5.png"); // Load your PNG image
    SDL_Surface *snake3 = IMG_Load("grids/images/snake6.png"); // Load your PNG image
    SDL_Surface *snake4 = IMG_Load("grids/images/snake8.png"); // Load your PNG image

    // // // failure check
    // if (dice == NULL)
    // {
    //     printf("Failed to load dice: %s\n", IMG_GetError());
    //     return;
    // }

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

    // // // Init all dice
    // SDL_Texture *dice_texture = SDL_CreateTextureFromSurface(renderer, dice);

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



    // // Free all ladder Surface
    // SDL_FreeSurface(dice); // Free the surface after creating texture

    // Free all ladder Surface
    SDL_FreeSurface(ladder); // Free the surface after creating texture
    SDL_FreeSurface(ladder2);
    SDL_FreeSurface(ladder3);
    SDL_FreeSurface(ladder4);

    // Free all the snakes
    SDL_FreeSurface(snake);
    SDL_FreeSurface(snake2);
    SDL_FreeSurface(snake3);
    SDL_FreeSurface(snake4);

    // if (dice_texture == NULL) // failure check
    // {
    //     printf("Failed to create dice texture: %s\n", SDL_GetError());
    //     return;
    // }

    if (ladder_texture == NULL || ladder_texture2 == NULL || ladder_texture3 == NULL || ladder_texture4 == NULL) // failure check
    {
        printf("Failed to create ladder texture: %s\n", SDL_GetError());
        return;
    }

    if (snake_texture == NULL || snake_texture2 == NULL || snake_texture3 == NULL || snake_texture4 == NULL) // failure check
    {
        printf("Failed to create snake texture: %s\n", SDL_GetError());
        return;
    }

    // // place dice
    // draw_img(renderer, dice_texture, -2, 2, 0, 5, screen_x, screen_y, 1, 1, 0);

    // place ladder
    draw_img(renderer, ladder_texture, 6, 1, 8, 3, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, ladder_texture3, 26, 4, 28, 6, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture2, 33, 12, 35, 14, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture4, 12, 8, 14, 10, screen_x, screen_y, 1, 1, 0);

        // place snakes
    draw_img(renderer, snake_texture, 24, 0, 30, 4, screen_x, screen_y, 1, 1, 270);
    draw_img(renderer, snake_texture2, 14, 4, 18, 8, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, snake_texture3, 1, 2, 5, 6, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, snake_texture4, 20, 10, 24, 14, screen_x, screen_y, 1, 1, 0);
    

    // Free the image texture after rendering
    // SDL_DestroyTexture(dice_texture);
    SDL_DestroyTexture(ladder_texture);
    SDL_DestroyTexture(ladder_texture2);
    SDL_DestroyTexture(ladder_texture3);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snake_texture2);
    SDL_DestroyTexture(snake_texture3);

}

/*
* Creates the grid on the window and call image placement function
*/
void draw_grid(SDL_Renderer *renderer, TTF_Font *font) {
    int margin = 25; // margin size
    int rows = 40;
    int cols = 15;

    // calculate board dimensions
    int width = (cols * CELL_WIDTH);   // 5 cells horizontally
    int height = (rows * CELL_HEIGHT); // 25 rows vertically

    // calculate board position
    int screen_x = (SCREEN_WIDTH - width) / 2;   // Center horizontally
    int screen_y = (SCREEN_HEIGHT - height) / 2; // Center vertically

    // render board
    SDL_Rect board = {screen_x, screen_y, width, height}; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 214, 151, 213, 1);   // Set color to pinnk
    SDL_RenderFillRect(renderer, &board);                 // Fill the rectangle

    // Set the color for the grid lines (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

    for (int x = screen_x; x <= screen_x + width; x += CELL_WIDTH)
    {
        SDL_RenderDrawLine(renderer, x, screen_y, x, screen_y + height);
    } // vertical lines on board

    for (int y = screen_y; y <= screen_y + height; y += CELL_HEIGHT)
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
                int cellX = screen_x + col * CELL_WIDTH;
                int cellY = screen_y + row * CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (CELL_WIDTH - textSurface->w) / 2,
                    cellY + (CELL_HEIGHT - textSurface->h) / 2,
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
                int cellX = screen_x + col * CELL_WIDTH;
                int cellY = screen_y + row * CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (CELL_WIDTH - textSurface->w) / 2,
                    cellY + (CELL_HEIGHT - textSurface->h) / 2,
                    textSurface->w,
                    textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            } // column loop
        } // cond check for odd/even rows
    } // row loop

    // call to function that places all snakes and ladders on grid (hard coded)
    place_imgs(renderer, screen_x, screen_y);
} // draw_grid

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Grid Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Load font
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/fonts-go/Go-Bold.ttf", 16);

    if (font == NULL)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

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
        draw_grid(renderer, font);
        draw_dice(renderer, dice_texture);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up and quit SDL
    // Clean up and quit SDL
    if (dice_texture != NULL)
    {
        SDL_DestroyTexture(dice_texture); // Free the texture when quitting
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // SDL_DestroyTexture(currentImage);
    TTF_Quit();
    SDL_Quit();

    return 0;
}