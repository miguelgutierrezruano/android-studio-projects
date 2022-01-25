//
// Created by migue on 25/01/2022.
//

#include "snake_body.h"

using namespace basics;

namespace snake
{
    /*snake_body::snake_body()
    {
        sb_x = 300;
        sb_y = 300;
        sb_speed = 300;
        sb_direction = -1;
        sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
    }*/

    /*snake_body::snake_body(Cell sb_starting_cell)
    {
        sb_x = sb_starting_cell.mid_point.coordinates.x();
        sb_y = sb_starting_cell.mid_point.coordinates.y();
        sb_speed = 300;
        sb_direction = -1;
        sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
        sb_current_cell = sb_starting_cell;
    }*/

    /*void snake_body::draw_snake_body(Canvas &canvas)
    {
        canvas.set_color(0.26f, 0.6f, 0.97f);
        canvas.fill_rectangle(sb_drawPosition, { snake_size, snake_size });
    }*/

    /*float snake_body::sb_distance(Vector2f p1, Vector2f p2)
    {
        float dist;

        dist = sqrt(((p2[0] - p1[0]) * (p2[0] - p1[0])) + ((p2[1] - p1[1]) * (p2[1] - p1[1])));

        return dist;
    }*/

    /*void snake_body::sb_move(float deltaTime, Vector2f followed_position, float node_direction)
    {
        if((sb_direction == 1 || sb_direction == 3) && abs(sb_y - followed_position[1]) < 5)
        {
            //el nodo anterior esta en horizontal
            if(sb_x - followed_position.coordinates.x() < 0)
            {
                //x tiene que disminuir
                sb_direction = 2;
                sb_y = followed_position[1];
            }
            else
            {
                sb_direction = 0;
                sb_y = followed_position[1];
            }

        }
        else if((sb_direction == 0 || sb_direction == 2) && abs(sb_x - followed_position[0]) < 5)
        {
            //el nodo anterior esta en vertical
            if(sb_y - followed_position.coordinates.y() < 0)
            {
                //y tiene que disminuir
                sb_direction = 3;
                sb_x = followed_position[0];
            }
            else
            {
                sb_direction = 1;
                sb_x = followed_position[0];
            }

        }


        if(node_direction == sb_direction && sb_distance( {sb_x, sb_y}, followed_position) < snake_size + 5) { }
        else if(sb_direction == 0)
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
    }*/
}
