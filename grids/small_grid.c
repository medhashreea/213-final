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
#define SMALL_CELL_WIDTH 50  // Width of each cell
#define SMALL_CELL_HEIGHT 35 // Height of each cell
#define FINAL_POS 124

char *player_imgs[4] = {"grids/images/character.png", "grids/images/character2.png", "grids/images/character3.png", "grids/images/character4.png"};

// data struct to hold state information
typedef enum
{
    die,  // wait state
    move, // moving spaces
    win   // end state
} state;

// data struct to hold player information
typedef struct player
{
    SDL_Texture *player_texture;
    int cur_position;
    state state;
} player_t;

/*
 * Ladder positions on the grid
 */
int small_ladders[3][2] = {{24, 33}, {62, 73}, {97, 106}};

/*
 * Snake positions on the grid
 */

int small_snakes[3][2] = {{27, 9}, {61, 42}, {118, 87}};

/*
 * Returns new position
 */
int snake_ladder_pos(int current_pos)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks if it's a snake
        if (current_pos == small_snakes[i][0])
        {
            current_pos = small_snakes[i][1];
            break;
        }
        // Checks if it's a ladder
        else if (current_pos == small_ladders[i][0])
        {
            current_pos = small_ladders[i][1];
            break;
        }
    }
    return current_pos;
}

/*
 * Checks if it's a snake or ladder
 */
bool snake_or_ladder(int current_pos)
{
    for (int i = 0; i < 3; i++)
    {
        if (current_pos == small_snakes[i][0] || current_pos == small_ladders[i][0])
        {
            return true;
        }
    }
    return false;
}

void move_player(SDL_Renderer *renderer, int current_pos, SDL_Texture *player_texture)
{
    // Board dimensions
    int rows = 25;
    int cols = 5;
    int cell_width = SMALL_CELL_WIDTH;
    int cell_height = SMALL_CELL_HEIGHT;

    // Calculate board position
    int screen_x = (SCREEN_WIDTH - (cols * cell_width)) / 2;   // Center horizontally
    int screen_y = (SCREEN_HEIGHT - (rows * cell_height)) / 2; // Center vertically

    // Calculate the character's grid position
    int row = current_pos / cols; // Determine row (integer division)
    int col;

    // if the row is even, increment the character (move right)
    if (row % 2 == 0)
    {
        col = current_pos % cols;
    }
    else // if the row is odd, decrement character (move left)
    {
        col = cols - 1 - (current_pos % cols);
    }

    // Calculate the character's pixel position
    int char_x = screen_x + col * cell_width;
    int char_y = screen_y + (rows - 1 - row) * cell_height; // Top-to-bottom layout

    // Render the character
    SDL_Rect character_rect = {char_x, char_y, cell_width, cell_height};
    SDL_RenderCopy(renderer, player_texture, NULL, &character_rect);

    // Present the updated frame
    // SDL_RenderPresent(renderer);

    // Cleanup
    // SDL_DestroyTexture(player_texture);
    IMG_Quit();
}

/**
 * Places the Snakes and Ladders images
 */
void place_small_imgs(SDL_Renderer *renderer, int screen_x, int screen_y)
{
    // Init all ladders (SDL_Surface)
    SDL_Surface *ladder = IMG_Load("grids/images/ladder.png");   // Load your PNG image
    SDL_Surface *ladder2 = IMG_Load("grids/images/ladder2.png"); // Load your PNG image
    SDL_Surface *ladder3 = IMG_Load("grids/images/ladder3.png"); // Load your PNG image

    SDL_Surface *snake = IMG_Load("grids/images/snake1.png");  // Load your PNG image
    SDL_Surface *snake2 = IMG_Load("grids/images/snake4.png"); // Load your PNG image
    SDL_Surface *snake3 = IMG_Load("grids/images/snake8.png"); // Load your PNG image

    if (ladder == NULL || ladder2 == NULL || ladder3 == NULL)
    {
        printf("Failed to load ladder image: %s\n", IMG_GetError());
        return;
    }

    if (snake == NULL || snake2 == NULL || snake3 == NULL)
    {
        printf("Failed to load snake image: %s\n", IMG_GetError());
        return;
    }

    // Init all ladders (SDL_Texture)
    SDL_Texture *ladder_texture = SDL_CreateTextureFromSurface(renderer, ladder);
    SDL_Texture *ladder_texture2 = SDL_CreateTextureFromSurface(renderer, ladder2);
    SDL_Texture *ladder_texture3 = SDL_CreateTextureFromSurface(renderer, ladder3);

    // Init all snakes (SDL_Texture)
    SDL_Texture *snake_texture = SDL_CreateTextureFromSurface(renderer, snake);
    SDL_Texture *snake_texture2 = SDL_CreateTextureFromSurface(renderer, snake2);
    SDL_Texture *snake_texture3 = SDL_CreateTextureFromSurface(renderer, snake3);

    // Free all ladder Surface
    SDL_FreeSurface(ladder); // Free the surface after creating texture
    SDL_FreeSurface(ladder2);
    SDL_FreeSurface(ladder3);

    // Free all the snakes
    SDL_FreeSurface(snake);
    SDL_FreeSurface(snake2);
    SDL_FreeSurface(snake3);

    if (ladder_texture == NULL || ladder_texture2 == NULL || ladder_texture3 == NULL) // failure check
    {
        printf("Failed to create ladder texture: %s\n", SDL_GetError());
        return;
    }

    if (snake_texture == NULL || snake_texture2 == NULL || snake_texture3 == NULL) // failure check
    {
        printf("Failed to create snake texture: %s\n", SDL_GetError());
        return;
    }

    // place ladder
    draw_img(renderer, ladder_texture, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 3, 1, 5, 3, screen_x, screen_y, 1, 1, 90);
    draw_img(renderer, ladder_texture2, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 18, 2, 20, 4, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, ladder_texture3, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 10, 1, 12, 3, screen_x, screen_y, 1, 1, 0);

    // place snakes
    draw_img(renderer, snake_texture, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 13, 0, 15, 2, screen_x, screen_y, 1, 1, 270);
    draw_img(renderer, snake_texture2, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 18, -1, 23, 2, screen_x, screen_y, 1, 1, 0);
    draw_img(renderer, snake_texture3, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 1, -1, 6, 2, screen_x, screen_y, 1, 1, 90);

    SDL_DestroyTexture(ladder_texture);
    SDL_DestroyTexture(ladder_texture2);
    SDL_DestroyTexture(ladder_texture3);
    SDL_DestroyTexture(snake_texture);
    SDL_DestroyTexture(snake_texture2);
    SDL_DestroyTexture(snake_texture3);
}

/**
 * Creates the grid on the window and call image placement function
 */
void small_grid(SDL_Renderer *renderer, TTF_Font *font)
{
    int margin = 25; // margin size
    int rows = 25;
    int cols = 5;

    // calculate board dimensions
    int width = (cols * SMALL_CELL_WIDTH);   // 5 cells horizontally
    int height = (rows * SMALL_CELL_HEIGHT); // 25 rows vertically

    // calculate board position
    int screen_x = (SCREEN_WIDTH - width) / 2;   // Center horizontally
    int screen_y = (SCREEN_HEIGHT - height) / 2; // Center vertically

    // render board
    SDL_Rect board = {screen_x, screen_y, width, height}; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 214, 151, 213, 1);   // Set color to pinnk
    SDL_RenderFillRect(renderer, &board);                 // Fill the rectangle

    // Set the color for the grid lines (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

    for (int x = screen_x; x <= screen_x + width; x += SMALL_CELL_WIDTH)
    {
        SDL_RenderDrawLine(renderer, x, screen_y, x, screen_y + height);
    } // vertical lines on board

    for (int y = screen_y; y <= screen_y + height; y += SMALL_CELL_HEIGHT)
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
                // move_player(number);

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
                int cellX = screen_x + col * SMALL_CELL_WIDTH;
                int cellY = screen_y + row * SMALL_CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (SMALL_CELL_WIDTH - textSurface->w) / 2,
                    cellY + (SMALL_CELL_HEIGHT - textSurface->h) / 2,
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
                // renderPlayer(renderer, number);

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
                int cellX = screen_x + col * SMALL_CELL_WIDTH;
                int cellY = screen_y + row * SMALL_CELL_HEIGHT;
                SDL_Rect textRect = {
                    cellX + (SMALL_CELL_WIDTH - textSurface->w) / 2,
                    cellY + (SMALL_CELL_HEIGHT - textSurface->h) / 2,
                    textSurface->w,
                    textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            } // column loop
        } // cond check for odd/even rows
    } // row loop

    // call to function that places all snakes and ladders on grid (hard coded)
    place_small_imgs(renderer, screen_x, screen_y);

} // small_grid

/**
 * small_grid_game
 * pre-conditions:
 * post-condictions:
 * description:
 */
void small_grid_game(SDL_Renderer *renderer, TTF_Font *font, int num_players)
{
    srand(time(NULL));      // init to generate random values later
    IMG_Init(IMG_INIT_PNG); // Initialize support for PNGs

    int quit = 0;
    SDL_Event e;
    SDL_Texture *dice_texture = NULL; // Variable to hold the current dice texture

    // init num_players & characters
    player_t *players[num_players];

    for (int i = 0; i < num_players; i++)
    {
        players[i] = malloc(sizeof(player_t)); // Allocate memory for each player

        if (players[i] == NULL)
        {
            printf("Memory allocation failed for player %d\n", i);
            return;
        }

        players[i]->cur_position = 0; // init player pos to 0
        players[i]->state = die;

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
    bool game_done = false; // while the user is in the small snakes & ladders window

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
                    printf("You rolled a %d \n", dice_value + 1);

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
                    // printf("cur_p: %d \n pos: %d \n img: %s \n", cur_p, players[cur_p]->cur_position, player_imgs[cur_p]);
                    players[cur_p]->state = move;
                } // Check if left mouse button was clicked
            }

            // checking for move state
            if (players[cur_p]->state == move)
            {
                while (cur_dice_step <= dice_value + 1) // while dice value is not reached
                {
                    printf("die step at: %d \n", cur_dice_step);
                    players[cur_p]->cur_position++;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);

                    // Check for win condition
                    if (players[cur_p]->cur_position >= FINAL_POS)
                    {
                        small_grid(renderer, font);
                        move_player(renderer, FINAL_POS, players[cur_p]->player_texture);
                        players[cur_p]->state = win;
                        game_done = true;
                        SDL_Delay(250);
                        break;
                    }

                    small_grid(renderer, font); // Redraw the grid

                    draw_dice(renderer, dice_texture); // Draw the dice texture

                    for (int i = 0; i < num_players; i++) // Render all players in their positions
                    {
                        move_player(renderer, players[i]->cur_position, players[i]->player_texture);
                    }

                    move_player(renderer, players[cur_p]->cur_position, players[cur_p]->player_texture); // Draw the player at the new position

                    SDL_Delay(250); // 200 ms delay for smooth movement

                    SDL_RenderPresent(renderer);

                    cur_dice_step++;
                }

                // Check for snakes or ladders after player has landed on final cell
                if (snake_or_ladder(players[cur_p]->cur_position))
                {
                    players[cur_p]->cur_position = snake_ladder_pos(players[cur_p]->cur_position);
                }
                printf("cur_p: %d \n pos: %d \n img: %s \n", cur_p, players[cur_p]->cur_position, player_imgs[cur_p]);

                cur_dice_step = 0;           // Reset step counter for next turn
                players[cur_p]->state = die; // Back to die state to wait for next roll
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
            SDL_RenderClear(renderer);
            small_grid(renderer, font);
            draw_dice(renderer, dice_texture);

            for (int i = 0; i < num_players; i++) // Render all players in their positions
            {
                move_player(renderer, players[i]->cur_position, players[i]->player_texture);
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
                small_grid(renderer, font);
                draw_img(renderer, winner_texture, SMALL_CELL_WIDTH, SMALL_CELL_HEIGHT, 10, -1, 20, 3, SCREEN_WIDTH, SCREEN_HEIGHT, 1, 1, 0);
                SDL_RenderPresent(renderer);
                SDL_Delay(1000); // delay for smooth movement
                break;
            }
        } // While
          
        if (cur_p == num_players - 1)
        {
            cur_p = 0;
        }// if on the last player and no player has won, p == 0 to circle back
    } // while not quit loop

    // Cleanup the textures after the game loop or when done
    for (int i = 0; i < num_players; i++)
    {
        SDL_DestroyTexture(players[i]->player_texture); // Free the player texture
        free(players[i]);                               // Free the player struct
    } // clean up loop
} // small_grid_game loop