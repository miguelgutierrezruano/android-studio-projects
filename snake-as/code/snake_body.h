//
// Created by migue on 25/01/2022.
//

#include "cell.h"
#include "helper.h"
#include <basics/Vector>
#include <basics/Canvas>
#include <basics/Timer>
#include <iostream>
#include <cmath>

using namespace basics;
using namespace std;

namespace snake
{
    class snake_body
    {
    public:

        static constexpr float snake_size = 40;
        static constexpr float snake_half_size = snake_size / 2;


        float sb_x, sb_y;
        float sb_speed;
        int sb_direction;
        Cell sb_current_cell;
        Vector2f sb_drawPosition;
        bool isVisible;
        Timer timerVisible;

        snake_body()
        {
            sb_x = 300;
            sb_y = 300;
            sb_speed = 300;
            sb_direction = -1;
            sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            isVisible = true;
        }

        snake_body(Cell sb_starting_cell)
        {
            sb_x = sb_starting_cell.mid_point.coordinates.x();
            sb_y = sb_starting_cell.mid_point.coordinates.y();
            sb_speed = 300;
            sb_direction = -1;
            sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            sb_current_cell = sb_starting_cell;
            isVisible = true;
        }

        snake_body(Cell sb_starting_cell, float starting_direction)
        {
            sb_x = sb_starting_cell.mid_point.coordinates.x();
            sb_y = sb_starting_cell.mid_point.coordinates.y();
            sb_speed = 0;
            sb_direction = starting_direction;
            sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            sb_current_cell = sb_starting_cell;
            isVisible = true;
        }

        snake_body(Vector2f pos, float starting_direction)
        {
            sb_x = pos[0];
            sb_y = pos[1];
            sb_speed = 0;
            sb_direction = starting_direction;
            sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            isVisible = true;
        }

        void draw_snake_body(Canvas & canvas)
        {
            canvas.set_color(0.26f, 0.6f, 0.97f);
            canvas.fill_rectangle(sb_drawPosition, { snake_size, snake_size });
        }

        void sb_move(float deltaTime, Vector2f followed_position, int node_direction)
        {
            //check distance for speed interval
            if(node_direction == sb_direction &&
               helper::distance( {sb_x, sb_y}, followed_position) < snake_size + 5)
            {
                sb_speed = 50;
            }
            else if(node_direction == sb_direction &&
                     helper::distance( {sb_x, sb_y}, followed_position) > snake_size + 10)
            {
                sb_speed = 350;
            }
            else { sb_speed = 300; }


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

            if(timerVisible.get_elapsed_seconds() > 0.03)
                isVisible = true;
            else
                isVisible = false;
        }

        void sb_change_direction(int _direction)
        {
            sb_direction = _direction;
        }

        bool contains (const basics::Vector2f & point) const
        {
            return
                    point[0] > sb_drawPosition[0] &&
                    point[1] > sb_drawPosition[1] &&
                    point[0] < sb_drawPosition[0] + snake_size &&
                    point[1] < sb_drawPosition[1] + snake_size;
        }



    };
}

