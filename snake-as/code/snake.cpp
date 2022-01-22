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

    void Snake::change_direction(int _direction)
    {
        direction = _direction;
    }
}




