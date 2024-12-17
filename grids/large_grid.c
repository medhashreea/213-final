/*
 * large_grid.c
 * The snakes and ladders game on a large grid.
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <FL/math.h>
#include <stdbool.h>
#include <time.h>
#include "../helpers/helpers.h"

#define SCREEN_WIDTH 1900    // Width of screen
#define SCREEN_HEIGHT 1000   // Height of screen
#define LARGE_CELL_WIDTH 35  // Width of each cell
#define LARGE_CELL_HEIGHT 19 // Height of each cell
#define LARGE_FINAL_POS 2499
#define LARGE_ROWS 50
#define LARGE_COLS 25

// Ladder positions on the grid
int large_ladders[5][2] = {{24, 33}, {62, 73}, {97, 106}};

// Snake positions on the grid
int large_snakes[5][2] = {{27, 9}, {61, 42}, {118, 87}};

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
    // calculate board dimensions
    int width = (LARGE_COLS * LARGE_CELL_WIDTH);   // 5 cells horizontally
    int height = (LARGE_ROWS * LARGE_CELL_HEIGHT); // 25 LARGE_ROWS vertically

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
    for (int row = LARGE_ROWS - 1; (row <= LARGE_ROWS) && (row >= 0); row--) // loop over all LARGE_ROWS first
    {
        if ((row % 2) != 0) // check if row is even
        {
            for (int col = 0; col < LARGE_COLS; col++) // for columns going left to right, increment
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
            for (int col = LARGE_COLS - 1; (col <= LARGE_COLS) && (col >= 0); col--) // for columns going right to left , decrement
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
        } // cond check for odd/even LARGE_ROWS
    } // row loop

    // call to function that places all snakes and ladders on grid (hard coded)
    place_large_imgs(renderer, screen_x, screen_y);
} // large_grid

/**
 * plays the game and calls other functions as needed
 *
 * \param renderer - a pointer to the renderer
 * \param font - a pointer to the font
 * \param num_players - integer that represents the number of players
 */
void large_grid_game(SDL_Renderer *renderer, int num_players)
{
    // Load font
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/fonts-go/Go-Bold.ttf", 12);

    if (font == NULL)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        return;
    }

    srand(time(NULL));      // init to generate random values later
    IMG_Init(IMG_INIT_PNG); // Initialize support for PNGs

    // Main loop flag
    int quit = 0;
    SDL_Event e;
    SDL_Texture *dice_texture = NULL; // Variable to hold the current dice texture

    player_t *players[num_players]; // init num_players & characters

    for (int i = 0; i < num_players; i++)
    {
        players[i] = malloc(sizeof(player_t)); // Allocate memory for each player

        if (players[i] == NULL)
        {
            printf("Memory allocation failed for player %d\n", i);
            return;
        }

        players[i]->cur_position = 0; // init player pos to 0
        players[i]->state = die;      // init state

        // render the player
        SDL_Surface *player_surface = IMG_Load(player_imgs[i]); // load the character image

        if (player_surface == NULL)
        {
            printf("Failed to load player image: %s\n", IMG_GetError());
            return;
        }

        SDL_Texture *player_textures = SDL_CreateTextureFromSurface(renderer, player_surface);
        players[i]->player_texture = player_textures; // init player's texture

        SDL_FreeSurface(player_surface); // Free the surface after creating the texture
    } // loop to set up player(s)

    int dice_value;         // init for dice value
    int cur_dice_step = 0;  // init dice to start counting at 0
    bool game_done = false; // while the user is in the large snakes & ladders window

    while (!quit)
    {
        int cur_p = 0;
        for (cur_p = 0; cur_p < num_players; cur_p++)
        {
            // Handle events
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = 1; // goes back to main window
                }
                else if ((e.type == SDL_MOUSEBUTTONDOWN) && (e.button.button == SDL_BUTTON_LEFT) && (players[cur_p]->state == die))
                {
                    // Generate a random dice value and choose the corresponding texture
                    dice_value = rand() % 6;
                    cur_dice_step = 1;
                    char *dice_choice = dice_paths[dice_value];
                    // printf("You rolled a %d \n", dice_value + 1);

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
                    players[cur_p]->state = move;
                } // Check if left mouse button was clicked
            }

            // checking for move state
            if (players[cur_p]->state == move)
            {
                while (cur_dice_step <= dice_value + 1) // while dice value is not reached
                {
                    players[cur_p]->cur_position++;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                    // Check for win condition
                    if (players[cur_p]->cur_position >= LARGE_FINAL_POS)
                    {
                        large_grid(renderer, font);
                        move_player(renderer, LARGE_FINAL_POS, players[cur_p]->player_texture, SCREEN_WIDTH, SCREEN_HEIGHT, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, LARGE_ROWS, LARGE_COLS);
                        players[cur_p]->state = win;
                        game_done = true;
                        SDL_Delay(250);
                        break;
                    }

                    large_grid(renderer, font);        // Redraw the grid
                    draw_dice(renderer, dice_texture); // Draw the dice texture

                    for (int i = 0; i < num_players; i++)
                    {
                        move_player(renderer, players[i]->cur_position, players[i]->player_texture, SCREEN_WIDTH, SCREEN_HEIGHT, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, LARGE_ROWS, LARGE_COLS);
                    } // Render all players in their positions

                    move_player(renderer, players[cur_p]->cur_position, players[cur_p]->player_texture, SCREEN_WIDTH, SCREEN_HEIGHT, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, LARGE_ROWS, LARGE_COLS); // Draw the player at the new position

                    SDL_Delay(250); // 200 ms delay for smooth movement
                    SDL_RenderPresent(renderer);
                    cur_dice_step++;
                }

                // Check for snakes or ladders after player has landed on final cell
                if (snake_or_ladder(players[cur_p]->cur_position, large_ladders, 3, large_snakes, 3))
                {
                    players[cur_p]->cur_position = snake_ladder_pos(players[cur_p]->cur_position, large_ladders, 3, large_snakes, 3);
                }

                cur_dice_step = 0;           // Reset step counter for next turn
                players[cur_p]->state = die; // Back to die state to wait for next roll
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
            SDL_RenderClear(renderer);
            large_grid(renderer, font);
            draw_dice(renderer, dice_texture);

            for (int i = 0; i < num_players; i++) // Render all players in their positions
            {
                move_player(renderer, players[i]->cur_position, players[i]->player_texture, SCREEN_WIDTH, SCREEN_HEIGHT, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, LARGE_ROWS, LARGE_COLS);
            }

            SDL_RenderPresent(renderer);

            if (game_done || players[cur_p]->state == win)
            {
                SDL_RenderClear(renderer);
                SDL_Surface *winner = IMG_Load("grids/images/winner.png"); // Load your PNG image

                if (winner == NULL)
                {
                    printf("Failed to load ladder image: %s\n", IMG_GetError());
                    return;
                }

                // Init all ladders (SDL_Texture)
                SDL_Texture *winner_texture = SDL_CreateTextureFromSurface(renderer, winner);

                SDL_FreeSurface(winner);

                if (winner_texture == NULL) // failure check
                {
                    printf("Failed to create ladder texture: %s\n", SDL_GetError());
                    return;
                }

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
                SDL_RenderClear(renderer);
                large_grid(renderer, font);
                draw_img(renderer, winner_texture, LARGE_CELL_WIDTH, LARGE_CELL_HEIGHT, 10, -1, 20, 3, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1, 0);
                SDL_RenderPresent(renderer);
                SDL_Delay(1000); // delay for smooth movement
                break;
            }
        } // While

        if (cur_p == num_players - 1)
        {
            cur_p = 0;
        } // if on the last player and no player has won, p == 0 to circle back
    } // while not quit loop

    // Cleanup the textures after the game loop or when done
    for (int i = 0; i < num_players; i++)
    {
        SDL_DestroyTexture(players[i]->player_texture); // Free the player texture
        free(players[i]);                               // Free the player struct
    } // clean up loop
} // large_grid_game loop