// #include <stdio.h>
// #include <stdbool.h>
// #include <SDL2/SDL_ttf.h>
// #include <SDL2/SDL.h>

// #include "helpers/scheduler.h"
// #include "helpers/util.h"

// int main (int argc, char** argv) {


// int cur_pos;

//     // Task handles each of the game tasks
//     task_t draw_board_task;
//     task_t move_character_task;
//     task_t roll_die_task;

//     // Initialize the schduler library 
//     scheduler_init();

//     // Create tasks for each task in the game 
//     task_create(&draw_board_task, draw_board);
//     task_create(&move_character_task, move_player(cur_pos));
//     task_create(&roll_die_task, roll_die);

//     // Wait for these tasks to exit 
//     task_wait(draw_board_task);
//     task_wait(move_character_task);
//     task_wait(roll_die_task);

//     end_game(cur_pos);

// }