#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 950
#define CELL_WIDTH 50  // Width of each cell
#define CELL_HEIGHT 50 // Height of each cell

void drawGrid(SDL_Renderer *renderer) {
    int margin = 25; // margin size
    int rows = 25;
    int cols = 5;

    // calculate board dimensions
    int width = (cols * CELL_WIDTH);    // 5 cells horizontally
    int height = (rows * CELL_HEIGHT); // 25 rows vertically

    // calculate board position
    int screen_x = (SCREEN_WIDTH - width) / 2;   // Center horizontally
    int screen_y = (SCREEN_HEIGHT - height) / 2; // Center vertically

    // render board
    SDL_Rect board = {screen_x, screen_y, width, height}; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);     // Set color to red
    SDL_RenderFillRect(renderer, &board);                 // Fill the rectangle

    // Set the color for the grid lines (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

    for (int x = screen_x; x <= screen_x + width; x += CELL_WIDTH) {
        SDL_RenderDrawLine(renderer, x, screen_y, x, screen_y + height);
    } // vertical lines on board

    for (int y = screen_y; y <= screen_y + height; y += CELL_HEIGHT) {
        SDL_RenderDrawLine(renderer, screen_x, y, screen_x + width, y);
    } // horizontal lines on board

    // add values in boxes
    for (int i = 1; i < rows * cols; i++) {
        // TODO: traverse through alls cells and label values
    }

    SDL_RenderPresent(renderer); // render the screen with the board and grid
}

int main(int argc, char *argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
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

        // Draw the grid
        drawGrid(renderer);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}