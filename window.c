#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

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

int main(int argc, char ** argv) {
    bool quit = false; // quit status
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Snakes and Ladders",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0); // create window of wxh
    
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0); // renders window


    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 250); // window color
        SDL_RenderClear(renderer); // makes white
        SDL_RenderPresent(renderer); // makes it appear
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    } // while not quit

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}