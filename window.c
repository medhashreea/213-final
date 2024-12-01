#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>

// Macros
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720


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
void intro_screen(renderer, font) {
        // calculate board position
    int screen_x = SCREEN_WIDTH / 2;   // Center horizontally
    int screen_y = SCREEN_HEIGHT / 2; // Center vertically

    // render board
    SDL_Rect board = {screen_x, screen_y, SCREEN_WIDTH, SCREEN_HEIGHT}; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 214, 151, 213, 1);     // Set color to pinnk
    SDL_RenderFillRect(renderer, &board);                 // Fill the rectangle

    // Set the color for the grid lines (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

    
    
}


int main(int argc, char ** argv) {
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

    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Opening window
        intro_screen(renderer, font);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up and quit SDL
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // SDL_DestroyTexture(currentImage);
    TTF_Quit();
    SDL_Quit();

    return 0;
}