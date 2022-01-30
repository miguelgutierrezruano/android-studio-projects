/*
 * SNAKE_BODY
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#include "snake_body.h"

using namespace basics;

namespace snake
{
    /*
    snake_body::snake_body(Cell sb_starting_cell)
    {
        sb_x = sb_starting_cell.mid_point.coordinates.x();
        sb_y = sb_starting_cell.mid_point.coordinates.y();
        sb_speed = 350;
        sb_direction = -1;
        sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
        sb_current_cell = sb_starting_cell;
        isVisible = true;
    }

    snake_body::snake_body(Cell sb_starting_cell, float starting_direction)
    {
        sb_x = sb_starting_cell.mid_point.coordinates.x();
        sb_y = sb_starting_cell.mid_point.coordinates.y();
        sb_speed = 0;
        sb_direction = starting_direction;
        sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
        sb_current_cell = sb_starting_cell;
        isVisible = true;
    }

    snake_body::snake_body(Vector2f pos, float starting_direction)
    {
        sb_x = pos[0];
        sb_y = pos[1];
        sb_speed = 0;
        sb_direction = starting_direction;
        sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
        isVisible = true;
    }

    void snake_body::sb_move(float deltaTime, Vector2f followed_position, int node_direction)
    {
        //check distance for speed interval

        if(node_direction == sb_direction &&
           helper::distance( {sb_x, sb_y}, followed_position) < snake_size - 5)
        {
            sb_speed = 200;
        }
        else if(node_direction == sb_direction &&
                helper::distance( {sb_x, sb_y}, followed_position) > snake_size)
        {
            sb_speed = 400;
        }
        else { sb_speed = 350; }


        if(sb_direction == 0)
        {
            sb_x -= sb_speed * deltaTime;
        }
        else if(sb_direction == 1)
        {
            sb_y -= sb_speed * deltaTime;
        }
        else if(sb_direction == 2)
        {
            sb_x += sb_speed * deltaTime;
        }
        else if(sb_direction == 3)
        {
            sb_y += sb_speed * deltaTime;
        }

        sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };

        if(timerVisible.get_elapsed_seconds() > 0.02f)
            isVisible = true;
        else
            isVisible = false;
    }
    */

}
