#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 950
#define CELL_WIDTH 50  // Width of each cell
#define CELL_HEIGHT 50 // Height of each cell

// void addIMG(SDL_Renderer *renderer) {

// }

void drawGrid(SDL_Renderer *renderer, TTF_Font *font)
{
    int margin = 25; // margin size
    int rows = 25;
    int cols = 5;

    // calculate board dimensions
    int width = (cols * CELL_WIDTH);   // 5 cells horizontally
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
    int number = -19;
    char numStr[10];

    for (int row = rows; (row <= rows) && (row >= 0); row--)
    {
        if ((row % 2) != 0)
        {
            for (int col = 0; col < cols; col++)
            {
                // check if row is even or odd
                // char numStr[10];
                snprintf(numStr, sizeof(numStr), "%d", number++);

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
            for (int col = cols - 1; (col <= cols) && (col >= 0); col--)
            {
                // char numStr[10];
                snprintf(numStr, sizeof(numStr), "%d", number++);

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

    IMG_Init(IMG_INIT_PNG); // initialize support for pngs
    SDL_Surface *ladder = IMG_Load("images/ladder.png");
    SDL_Texture *ladder_texture = SDL_CreateTextureFromSurface(renderer, ladder);
    IMG_Quit();
} // drawGrid

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
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/fonts-go/Go-Bold.ttf", 24);

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

        // Draw the grid
        drawGrid(renderer, font);

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