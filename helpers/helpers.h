#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>

// data struct for scheduler
typedef enum
{
    die,  // wait state
    move, // moving spaces
    win   // end state
} State;

// data struct to hold player information
typedef struct player
{
    SDL_Texture *player_texture; // players img
    int cur_position;            // player's current postion
    State state;                 // player's state
} player_t;

// Array of dice paths
extern char *dice_paths[]; // Declare as external to avoid redefinition errors

// Array of characters
extern char *player_imgs[]; // Declare as external to avoid redefinition errors

// Function to draw the dice
void draw_dice(SDL_Renderer *renderer, SDL_Texture *dice_texture);

// Function to draw a diagonal ladder between two points
void draw_img(SDL_Renderer *renderer, SDL_Texture *ladder_texture, int CELL_WIDTH, int CELL_HEIGHT, int startRow, int startCol, int endRow, int endCol, int screen_x, int screen_y, double scale_x, double scale_y, int turn);

// Returns the new snake or ladder position
int snake_ladder_pos(int current_pos, int ladders[][2], int num_ladders, int snakes[][2], int num_snakes);

// Detrmines if the position is a snake or ladder
bool snake_or_ladder(int current_pos, int ladders[][2], int num_ladders, int snakes[][2], int num_snakes);

// Moves the current player
void move_player(SDL_Renderer *renderer, int current_pos, SDL_Texture *player_texture, int SCREEN_WIDTH, int SCREEN_HEIGHT, int CELL_WIDTH, int CELL_HEIGHT);
