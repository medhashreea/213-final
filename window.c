#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>

#include "grids/small_grid.c"

// Macros
// #define SCREEN_WIDTH 1280
// #define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1000

typedef struct
{
    SDL_Rect rect;   // Position and size of the button
    SDL_Color color; // Color of the button
} Button;
/**
 * GRAPHICS TODO (25x5, 50x10, 100x50) - each grid is different file
 * 1. build grid
 * 2. add the numbers
 * 3. add the snakes and ladders
 * 4. add the players (threading - thread for each player, thread synch moves)
 * 5. generate dice (1-6)
 * 6. move players around based dice value (scheduling)
 *
 * AFTER basic graphics
 * 1. create opening window/screen choices (grid choice & # of player choice)
 * 2. based on selection, change window/screen to respective grid with respective number of players
 * 3. play game
 * 4. closing rank window/screen
 *
 * IF FINISH EARLY
 * 1. add networking >_<
 */
// void intro_screen(SDL_Renderer *renderer, TTF_Font *font)
// {
//     // MAIN BACKDROP
//     int margin = 25;                              // margin size
//     int rect_width = SCREEN_WIDTH - margin;   // Adjust width considering the margin
//     int rect_height = SCREEN_HEIGHT - margin; // Adjust height considering the margin

//     // Calculate the position to center the rectangle
//     int screen_x = (SCREEN_WIDTH - rect_width) / 2;
//     int screen_y = (SCREEN_HEIGHT - rect_height) / 2;

//     // main backdrop render
//     SDL_Rect board = {screen_x, screen_y, rect_width, rect_height};
//     SDL_SetRenderDrawColor(renderer, 207, 181, 163, 1); // color
//     SDL_RenderFillRect(renderer, &board);               // fill

//     // SUB-BACKDROPS - GRID CHOICE BOXES
//     int grid_pick_width = rect_width / 3;
//     int grid_pick_height = rect_height / 5;
//     int grid_pick_y = screen_y * 20;

//     // small grid choice box placement
//     SDL_Rect sm_grid = {screen_x * 3, grid_pick_y, grid_pick_width, grid_pick_height};
//     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1); // color
//     SDL_RenderFillRect(renderer, &sm_grid);       // fill

//     SDL_BUTTON

//     // // medium grid choice box placement
//     // SDL_Rect md_grid = {screen_x/2, grid_pick_y, grid_pick_width, grid_pick_height};
//     // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1); // color
//     // SDL_RenderFillRect(renderer, &md_grid);       // fill

//     // // large grid choice box placement
//     // SDL_Rect lg_grid = {screen_x * 35, grid_pick_y, grid_pick_width, grid_pick_height};
//     // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 1); // color
//     // SDL_RenderFillRect(renderer, &lg_grid);       // fill
// }
void intro_screen(SDL_Renderer *renderer, TTF_Font *font, Button button)
{
    // Main backdrop (existing code)
    int margin = 25;
    int rect_width = SCREEN_WIDTH - margin;
    int rect_height = SCREEN_HEIGHT - margin;
    int screen_x = (SCREEN_WIDTH - rect_width) / 2;
    int screen_y = (SCREEN_HEIGHT - rect_height) / 2;
    SDL_Rect board = {screen_x, screen_y, rect_width, rect_height};
    SDL_SetRenderDrawColor(renderer, 207, 181, 163, 255);
    SDL_RenderFillRect(renderer, &board);

    // Draw the button
    SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
    SDL_RenderFillRect(renderer, &button.rect);
}

int main(int argc, char **argv)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize SDL_ttf (font)
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
        SDL_DestroyWindow(window);
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

    SDL_Point mousePos;
    Button button = {
        .rect = {200, 200, 200, 50}, // Example button location and size
        .color = {255, 0, 0, 255}    // Red color
    };

    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                SDL_Point mousePos;
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                if (SDL_PointInRect(&mousePos, &button.rect))
                {
                    small_grid_game(renderer, font); // Pass existing renderer and font to the game
                    SDL_SetWindowTitle(window, "Small Snakes & Ladder");
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Opening window
        intro_screen(renderer, font, button); // create backdrop

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up and quit SDL
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}