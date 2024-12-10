#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "helpers/sfunc.h"

// #include "helpers/scheduler.h"
#include "helpers/util.h"

int main (int argc, char** argv) { 
    bool running = true; 
    position = 0;
    long long last_time = time_ms();
    draw_board(renderer, font);
    while(running) {
        int current_time = time_ms();
        int elapsed_time = current_time - last_time;
        roll_die();
        move_player(position);
    }
end_game();
}


// doesn't need to have task+t and stuff
    // have a loop while game is running 
    // just call the functions in there 


    // using time still scheduling 
    // time (ms), might be parameter, might be global, can call it multiple times 
    // while (running)
    // put the parameter global variables in the .h files 





/* int cur_pos;

    // Task handles each of the game tasks
    task_t draw_board_task;
    task_t move_character_task;
    task_t roll_die_task;

    // Initialize the schduler library 
    scheduler_init();

    // Create tasks for each task in the game 
    task_create(&draw_board_task, draw_board);
    task_create(&move_character_task, move_player(cur_pos));
    task_create(&roll_die_task, roll_die);

    // Wait for these tasks to exit 
    task_wait(draw_board_task);
    task_wait(move_character_task);
    task_wait(roll_die_task);

    end_game(cur_pos);

*/