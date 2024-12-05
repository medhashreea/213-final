#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include "scheduler.h"

#include <assert.h>
#include <curses.h>
#include <ucontext.h>

#include "util.h"

// We might also want a task like isSnake or isLadder (I'm not reallly sure how it would check that though like would it ask is png or)

/**
 * Find the next available task to run
 *
 * \returns the index of the naxt available task
 */
task_t find_task();

// This is an upper limit on the number of tasks we can create.
#define MAX_TASKS 128

// This is the size of each task's stack memory
#define STACK_SIZE 65536

// This stores the state of the task
typedef enum {ready, waiting, done} States;
// This stores the directions 
typedef enum {up, left, right, snake, ladder} Directions;

// for small grid
// if row is odd state should be set to right 
// if row is even state should be set to left
//

// or should state be direction (then can set direction to either up, left, right)


// This struct will hold the all the necessary information for each task
typedef struct task_info {
  // This field stores all the state required to switch back to this task
  ucontext_t context;

  // This field stores another context. This one is only used when the task
  // is exiting.
  ucontext_t exit_context;

  // Task's state
  States states;

  // Task's direction
  Directions directions;

  // The task that the current task is waiting for
  task_t previousTask;

  // The number of spaces it should move based on the die
  int spacesMoved;

  // Was the task blocked waiting for user input?
  bool isBlock;

  // Store the user input
  int input;
} task_info_t;

int current_task = 0;          //< The handle of the currently-executing task
int num_tasks = 1;             //< The number of tasks created so far
task_info_t tasks[MAX_TASKS];  //< Information for every task

/**
 * Initialize the scheduler. Programs should call this before calling any other
 * functiosn in this file.
 */
void scheduler_init() {
}


// What Ellie said: 
// save how many spaces it moved
// have a function task to move it 
// direction it's moving in 


/**
 * This function will execute when a task's function returns. This allows you
 * to update scheduler states and start another task. This function is run
 * because of how the contexts are set up in the task_create function.
 */
void task_exit() {
  // Handle the end of a task's execution
  tasks[current_task].states = done;

  // Find the next runnable task
  task_t old_task = current_task;
  current_task = find_task();
  swapcontext(&(tasks[old_task].context), &(tasks[current_task].context));
}

/**
 * Create a new task and add it to the scheduler.
 *
 * \param handle  The handle for this task will be written to this location.
 * \param fn      The new task will run this function.
 */
void task_create(task_t* handle, task_fn_t fn) {
  // Claim an index for the new task
  int index = num_tasks;
  num_tasks++;

  // Initializes the fields of the task_info
  tasks[index].states = ready;
  tasks[index].isBlock = false;

  // Set the task handle to this index, since task_t is just an int
  *handle = index;

  // We're going to make two contexts: one to run the task, and one that runs at the end of the task
  // so we can clean up. Start with the second

  // First, duplicate the current context as a starting point
  getcontext(&tasks[index].exit_context);

  // Set up a stack for the exit context
  tasks[index].exit_context.uc_stack.ss_sp = malloc(STACK_SIZE);
  tasks[index].exit_context.uc_stack.ss_size = STACK_SIZE;

  // Set up a context to run when the task function returns. This should call task_exit.
  makecontext(&tasks[index].exit_context, task_exit, 0);

  // Now we start with the task's actual running context
  getcontext(&tasks[index].context);

  // Allocate a stack for the new task and add it to the context
  tasks[index].context.uc_stack.ss_sp = malloc(STACK_SIZE);
  tasks[index].context.uc_stack.ss_size = STACK_SIZE;

  // Now set the uc_link field, which sets things up so our task will go to the exit context when
  // the task function finishes
  tasks[index].context.uc_link = &tasks[index].exit_context;

  // And finally, set up the context to execute the task function
  makecontext(&tasks[index].context, fn, 0);
}

/**
 * Wait for a task to finish. If the task has not yet finished, the scheduler should
 * suspend this task and wake it up later when the task specified by handle has exited.
 *
 * \param handle  This is the handle produced by task_create
 */
void task_wait(task_t handle) {
  // If tasks of handle is not equal to done, then current task waits and set previous
  // task to handle
  if (tasks[handle].states != done) {
    tasks[current_task].states = waiting;
    tasks[current_task].previousTask = handle;

    // finds the next task to run
    task_t old_task = current_task;
    current_task = find_task();
    swapcontext(&(tasks[old_task].context), &(tasks[current_task].context));
  }
}

/*
* Either should switch direction or move it in a specific direction 
*/
void direction_task() {

}

/**
 * Find the next available task to run
 *
 * \returns the index of the naxt available task
 */
task_t find_task() {
  // Start with the first task after current task
  task_t i = (current_task + 1) % num_tasks;
  int ch = getch();

  while (true) {
    if (tasks[i].states == ready) {
      return i;
    } else if (tasks[i].states == waiting && tasks[i].isBlock == false) {
      // check if the task that it's waiting on is done
      task_t prev_index = tasks[i].previousTask;
      if (tasks[prev_index].states == done) {
        tasks[i].states = ready;
        return i;
      }
    } else if (tasks[i].states == sleep && time_ms() >= tasks[i].time_to_wake_up) {
      // if the task is sleeping and the sleeping time has elapsed
      tasks[i].states = ready;  // Wake up the task
      return i;
    } else if (tasks[i].isBlock == true && ch != ERR) {
      // if the task is blocked for input and
      tasks[i].states = ready;
      tasks[i].isBlock = false;
      tasks[i].input = ch;
      return i;
    }

    // Move to next task
    i = (i + 1) % num_tasks;
  }
}
