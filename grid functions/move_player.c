#include <stdio.h>

/*
 * Returns new position
 */
int snake_ladder_pos(int cur_pos)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks if it's a snake
        if (cur_pos == large_snakes[i][0])
        {
            return large_snakes[i][1];
        }
        // Checks if it's a ladder
        else if (cur_pos == large_ladders[i][0])
        {
            return large_ladders[i][1];
        }
    }
    return cur_pos;
}

/*
 * Checks if it's a snake or ladder
 */
bool snake_or_ladder(int cur_pos)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks if it's a snake
        return (cur_pos == large_snakes[i][0] || cur_pos == large_ladders[i][0]);
    }
    return false;
}

void move_player(int cur_pos)
{
    if (snake_or_ladder(cur_pos))
    {
        snake_ladder_pos(cur_pos);
    }
    else
    {
        cur_pos += dice_value;
    }
}
