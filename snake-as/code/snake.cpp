//
// Created by migue on 19/01/2022.
//

#include "snake.h"


using namespace basics;

namespace snake
{


    void Snake::move(float deltaTime, vector<Pivot> & pivots)
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

        //SNAKE BODY
        for (int i = 0; i < sb.size(); ++i)
        {
            if(i != 0)
                sb[i].sb_move(deltaTime, { sb[i-1].sb_x, sb[i-1].sb_y }, sb[i-1].sb_direction);
            else
                sb[i].sb_move(deltaTime, { x, y }, direction);

            for (int j = 0; j < pivots.size(); ++j)
            {
                if(helper::distance(pivots[j].position, { sb[i].sb_x, sb[i].sb_y } ) < snake_half_size)
                {
                    //Solo las vuelve invisibles si se van a salir
                    if((sb[i].sb_direction == 0 && sb[i].sb_x < sb[i].sb_current_cell.mid_point[0]) ||
                    (sb[i].sb_direction == 1 && sb[i].sb_y < sb[i].sb_current_cell.mid_point[1]) ||
                    (sb[i].sb_direction == 2 && sb[i].sb_x > sb[i].sb_current_cell.mid_point[0]) ||
                    (sb[i].sb_direction == 3 && sb[i].sb_y > sb[i].sb_current_cell.mid_point[1]))
                        sb[i].timerVisible.reset();

                    if((sb[i].sb_direction == 0 && sb[i].sb_x <= pivots[j].position[0]) ||
                    (sb[i].sb_direction == 1 && sb[i].sb_y <= pivots[j].position[1]) ||
                    (sb[i].sb_direction == 2 && sb[i].sb_x >= pivots[j].position[0]) ||
                    (sb[i].sb_direction == 3 && sb[i].sb_y >= pivots[j].position[1]))
                    {
                        sb[i].sb_change_direction(pivots[j].turn_direction);

                        if(sb[i].sb_direction == 1 || sb[i].sb_direction == 3)
                        {
                            sb[i].sb_x = pivots[j].pivot_cell.mid_point[0];
                        }
                        else if(sb[i].sb_direction == 0 || sb[i].sb_direction == 2)
                        {
                            sb[i].sb_y = pivots[j].pivot_cell.mid_point[1];
                        }

                        //sobrecargar ==
                        if(sb[i].sb_x == sb.back().sb_x && sb[i].sb_y == sb.back().sb_y
                           && pivots[j].position == pivots.front().position)
                        {
                            //ultimo pivote
                            pivots.erase(pivots.begin());
                            pivots.shrink_to_fit();
                        }
                    }


                }
            }
        }



    }

    void Snake::calculate_current_cell(Cell (&board)[Cell::board_width][Cell::board_height])
    {
        for (int i = 0; i < Cell::board_width; ++i)
        {
            //Each row

            for (int j = 0; j < Cell::board_height; ++j) {

                if((j == 0 || j == Cell::board_height - 1) || (i == 0 || i == Cell::board_width - 1)) { }
                else
                    board[i][j].status = FREE;

                for (int k = 0; k < sb.size(); ++k) {
                    if(board[i][j].contains( { sb[k].sb_x, sb[k].sb_y } ))
                    {
                        sb[k].sb_current_cell = board[i][j];
                            board[i][j].status = OCCUPIED;

                    }
                }

                if(board[i][j].contains( { x, y } ))
                {

                    current_cell = board[i][j];


                }

            }

        }
    }

    void Snake::check_food_collision(Food & food, Cell (&board)[Cell::board_width][Cell::board_height])
    {

        if(helper::distance( { x, y }, food.get_position()) < (snake_half_size + food.food_half_size) - 20)
        {
            food.generate_food(board);

            sb.emplace_back(
                    snake_body({sb.back().sb_x, sb.back().sb_y}, sb.back().sb_direction)
                    //sb.back().sb_current_cell
            );
        }
    }

    bool Snake::check_endgame_collision()
    {
        if(current_cell.status == BORDER)
        {
            game_over();
            return true;
        }

        for (int i = 0; i < sb.size(); ++i) {
            if(i != 0 && i != 1)
            {
                if(sb[i].contains( { x, y } ))
                {
                    game_over();
                    return true;
                }

            }

        }
        return false;
    }


    void Snake::change_direction(int _direction)
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


            }

    }
}




