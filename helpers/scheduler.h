#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int position;
SDL_Renderer *renderer;
TTF_Font *font;


/**
 *  Draw board
 */

void draw_board (SDL_Renderer *renderer, TTF_Font *font);

/*
* Rolls the die
*/
void roll_die();

/*
* Moves the player
*/

void move_player(int cur_pos);

/*
* Ends the game
*/
void end_game();