//
// Created by migue on 19/01/2022.
//

#include "snake.h"

using namespace basics;

namespace snake
{


    void Snake::move(float deltaTime)
    {

        if(direction == 0)
        {
            x -= speed * deltaTime;
        }
        else if(direction == 1)
        {
            y -= speed * deltaTime;
        }
        else if(direction == 2)
        {
            x += speed * deltaTime;
        }
        else if(direction == 3)
        {
            y += speed * deltaTime;
        }
        else { }

        drawPosition = { x - snake_half_size, y - snake_half_size };

    }

    void Snake::calculate_current_cell(Cell board[board_swidth][board_sheight])
    {
        for (int i = 0; i < board_swidth; ++i)
        {
            //Each row

            for (int j = 0; j < board_sheight; ++j) {

                if(board[i][j].contains( { x, y } ))
                {

                    current_cell = board[i][j];
                }


            }

        }

        if(current_cell.status == OCCUPIED)
        {
            change_direction(-1);
            //Game over
        }
    }

    void Snake::change_direction(int _direction)
    {
        if(direction == 0 && _direction == 2) { }
        else if (direction == 1 && _direction == 3) { }
        else if (direction ==  2 && _direction == 0) { }
        else if (direction == 3 && _direction == 1) { }
        else if (_direction == -1) { direction = _direction; }
        else
            {
                direction = _direction;
                x = current_cell.mid_point.coordinates.x();
                y = current_cell.mid_point.coordinates.y();
            }

    }
}




