#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>
#include "helpers/helpers.h"
#include <pthread.h>

#include "grids/small_grid.c"
#include "grids/medium_grid.c"
#include "grids/large_grid.c"

// Macros
#define SCREEN_WIDTH 1900
#define SCREEN_HEIGHT 1000

pthread_t threads[4];

// make struct with renderer, cur_position, and each image corresponding to each thread manually

typedef struct player
{
    SDL_Renderer *renderer;
    int cur_position;
    SDL_Texture *player_texture;
} player_t;

// make struct that holds arguments
pthread_t *char_threads_array[4];

// void make_threads() {
// for (int i = 0; i < 4; i++) {
//     // Creates thread
//     if (pthread_create(&threads[i], NULL, move_player(player_t -> renderer, player_t-> cur_position), &char_threads_array[i])) {
//         perror("pthread_create failed");
//         exit(2);
//     }
//     // Waits for thread
//     if (pthread_join(threads[i], NULL)) {
//         perror("pthread_join failed");
//         exit(2);
//         }
//     }
// }

// malloc(sizeof);

// create threads, wait threads, synchronize

// create, wait, synchgrnoize

// struct character_array[4];

//

typedef struct
{
    SDL_Rect rect;   // Position and size of the button
    SDL_Color color; // Color of the button
    char *label;
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

void render_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, char *text, int x, int y)
{
    if (text == NULL || text[0] == '\0')
    {
        // Don't render if the text is empty
        return;
    }

    SDL_Surface *text_surface = TTF_RenderText_Blended(font, text, color);
    if (!text_surface)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);

    if (!text_texture)
    {
        printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    if (text_surface->w == 0 || text_surface->h == 0)
    {
        printf("Error: Rendered text surface has zero width or height!\n");
        SDL_FreeSurface(text_surface);
        return;
    }

    SDL_Rect text_rect = {x, y, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_DestroyTexture(text_texture);
}

void player_entry_box(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect *entry_box, SDL_Color text_color, char *input_text)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for the box
    SDL_RenderFillRect(renderer, entry_box);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black border for the box
    SDL_RenderDrawRect(renderer, entry_box);

    // Render the input text inside the box
    render_text(renderer, font, text_color, input_text, entry_box->x + 5, entry_box->y + 5); // Offset for padding
}

void intro_screen(SDL_Renderer *renderer, TTF_Font *font, Button small_board, Button medium_board, Button large_board)
{
    // Main backdrop
    int margin = 25;
    int rect_width = SCREEN_WIDTH - margin;
    int rect_height = SCREEN_HEIGHT - margin;
    int screen_x = (SCREEN_WIDTH - rect_width) / 2;
    int screen_y = (SCREEN_HEIGHT - rect_height) / 2;
    SDL_Rect board = {screen_x, screen_y, rect_width, rect_height};
    SDL_SetRenderDrawColor(renderer, 207, 181, 163, 255);
    SDL_RenderFillRect(renderer, &board);

    // Render the title at the top of the screen
    char *title = "SNAKES AND LADDERS";
    int title_x = (SCREEN_WIDTH - 300) / 2; // Centering title width (300 px wide)
    int title_y = 50;                       // Fixed top margin
    SDL_Color title_color = {255, 0, 255, 255};
    TTF_Font *title_font = TTF_OpenFont("/usr/share/fonts/fonts-go/Go-Bold.ttf", 48);
    render_text(renderer, title_font, title_color, title, title_x - 100, title_y);
    // // Set button positions at the bottom of the screen
    // int button_margin = 20; // Space between buttons and screen edges
    // int button_width = 200;
    // int button_height = 50;

    // // Center buttons at the bottom of the screen
    // small_board.rect.x = (SCREEN_WIDTH - 3 * button_width - 2 * button_margin) / 2;
    // small_board.rect.y = SCREEN_HEIGHT - button_height - button_margin;
    // small_board.rect.w = button_width;
    // small_board.rect.h = button_height;

    // medium_board.rect.x = small_board.rect.x + button_width + button_margin;
    // medium_board.rect.y = small_board.rect.y;
    // medium_board.rect.w = button_width;
    // medium_board.rect.h = button_height;

    // large_board.rect.x = medium_board.rect.x + button_width + button_margin;
    // large_board.rect.y = small_board.rect.y;
    // large_board.rect.w = button_width;
    // large_board.rect.h = button_height;

    // Draw the small board button
    SDL_SetRenderDrawColor(renderer, small_board.color.r, small_board.color.g, small_board.color.b, small_board.color.a);
    SDL_RenderFillRect(renderer, &small_board.rect);

    // Draw the medium board button
    SDL_SetRenderDrawColor(renderer, medium_board.color.r, medium_board.color.g, medium_board.color.b, medium_board.color.a);
    SDL_RenderFillRect(renderer, &medium_board.rect);

    // Draw the large board button
    SDL_SetRenderDrawColor(renderer, large_board.color.r, large_board.color.g, large_board.color.b, large_board.color.a);
    SDL_RenderFillRect(renderer, &large_board.rect);

    // Render labels for each button
    SDL_Color text_color = {0, 0, 0, 255}; // Black color for the text
    render_text(renderer, font, text_color, small_board.label, small_board.rect.x + (small_board.rect.w - 50) / 2, small_board.rect.y + (small_board.rect.h - 20) / 2);
    render_text(renderer, font, text_color, medium_board.label, medium_board.rect.x + (medium_board.rect.w - 50) / 2, medium_board.rect.y + (medium_board.rect.h - 20) / 2);
    render_text(renderer, font, text_color, large_board.label, large_board.rect.x + (large_board.rect.w - 50) / 2, large_board.rect.y + (large_board.rect.h - 20) / 2);
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
    SDL_Window *window = SDL_CreateWindow("Snakes & Ladders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    Button small_board = {
        .rect = {200, 200, 200, 50}, // button location and size
        .color = {255, 0, 0, 255},   // red
        .label = "Small board"};

    Button medium_board = {
        .rect = {SCREEN_WIDTH / 2 - 100, 200, 200, 50}, //  button location and size
        .color = {0, 255, 0, 255},                      // green color
        .label = "Medium board"};

    Button large_board = {
        .rect = {SCREEN_WIDTH - 400, 200, 200, 50}, //  button location and size
        .color = {0, 0, 255, 255},                  // blue color
        .label = "Large board"};

    // Add an entry box for the number of players
    SDL_Rect entry_box = {SCREEN_WIDTH / 2 - 100, 300, 200, 50};
    char num_player[2] = ""; // To hold the number of players as a string
    int num_length = 0;      // Length of current input

    // Entry box color
    SDL_Color num_color = {0, 0, 0, 255}; // Black for text

    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym >= SDLK_1 && e.key.keysym.sym <= SDLK_4 && num_length < 1) // only takes first number input
                {
                    // Add the key to num_player if within valid range (1-4)
                    num_player[num_length++] = e.key.keysym.sym - SDLK_0 + '0'; // Convert int to char
                    num_player[num_length] = '\0';                              // Null-terminate the string
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE && num_length > 0)
                {
                    // Remove the last character if backspace is pressed
                    num_length--;
                    num_player[num_length] = '\0'; // Null-terminate the string
                }
                else if (e.key.keysym.sym == SDLK_RETURN)
                {
                    // Process the number of players when Enter is pressed
                    if (num_length > 0)
                    {
                        int num_players = atoi(num_player);
                        if (num_players >= 1 && num_players <= 4)
                        {
                            // Handle the selected number of players
                            printf("Number of players: %d\n", num_players);
                            // Implement logic to start the game with 'num_players' here
                        }
                        else
                        {
                            printf("Invalid number of players. Please choose a number between 1 and 4.\n");
                        }
                        // Reset input for the next input
                        num_length = 0;
                        num_player[0] = '\0';
                    }
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int num_players = atoi(num_player); // convert char num to integer

                if (num_players == 0)
                {
                    num_players = 1;
                } // default num player to 1 player

                SDL_Point mousePos;
                SDL_GetMouseState(&mousePos.x, &mousePos.y);
                if (SDL_PointInRect(&mousePos, &small_board.rect))
                {
                    SDL_SetWindowTitle(window, "Small Game");       // change window name
                    small_grid_game(renderer, font, num_players);   // Call small game
                    SDL_SetWindowTitle(window, "Snakes & Ladders"); // change window name back
                }
                else if (SDL_PointInRect(&mousePos, &medium_board.rect))
                {
                    SDL_SetWindowTitle(window, "Medium Game");      // change window name
                    medium_grid_game(renderer, font, num_players);               // Call medium game
                    SDL_SetWindowTitle(window, "Snakes & Ladders"); // change window name back
                }
                else if (SDL_PointInRect(&mousePos, &large_board.rect))
                {
                    SDL_SetWindowTitle(window, "Large Game");       // change window name
                    large_grid_game(renderer, font, num_players);                // Call large game
                    SDL_SetWindowTitle(window, "Snakes & Ladders"); // change window name back
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Opening window
        intro_screen(renderer, font, small_board, medium_board, large_board); // create backdrop
        player_entry_box(renderer, font, &entry_box, num_color, num_player);
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