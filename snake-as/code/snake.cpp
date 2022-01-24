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

        sb.sb_move(deltaTime, { x, y }, direction);

        drawPosition = { x - snake_half_size, y - snake_half_size };

    }

    void Snake::calculate_current_cell(Cell board[Cell::board_width][Cell::board_height])
    {
        for (int i = 0; i < Cell::board_width; ++i)
        {
            //Each row

            for (int j = 0; j < Cell::board_height; ++j) {

                if(board[i][j].contains( { x, y } ))
                {

                    current_cell = board[i][j];
                }


            }

        }

        if(current_cell.status == OCCUPIED)
        {
            //change_direction(-1, );
            game_over();
            //Game over
        }

        sb.calculate_sb_current_cell(board);
    }

    void Snake::check_food_collision(Food & food, Cell board[Cell::board_width][Cell::board_height])
    {
        if(distance( { x, y }, food.get_position()) < (snake_half_size + food.food_half_size) - 20)
        {
            food.generate_food(board);
        }
    }

    float Snake::distance(Vector2f p1, Vector2f p2)
    {
        float dist;

        dist = sqrt(((p2[0] - p1[0]) * (p2[0] - p1[0])) + ((p2[1] - p1[1]) * (p2[1] - p1[1])));

        return dist;
    }


    void Snake::change_direction(int _direction, float & delay)
    {
        if(direction == 0 && _direction == 2) { }
        else if (direction == 1 && _direction == 3) { }
        else if (direction ==  2 && _direction == 0) { }
        else if (direction == 3 && _direction == 1) { }
        else if (direction == _direction) { }
        else if (_direction == -1) { direction = _direction; }
        else
            {
                direction = _direction;
                x = current_cell.mid_point.coordinates.x();
                y = current_cell.mid_point.coordinates.y();

                if(sb.sb_current_cell.position != current_cell.position)
                {
                    sb.sb_x = sb.sb_current_cell.mid_point[0];
                    sb.sb_y = sb.sb_current_cell.mid_point[1];
                }

                //Bajar delay si se sube la velocidad
                delay = 0.09f;
            }

    }
}




