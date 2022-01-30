/*
 * FOOD
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#include "Food.h"

using namespace basics;
using namespace std;

namespace snake
{
    /*Food::Food(Cell startingCell)
    {
        x = startingCell.mid_point.coordinates.x();
        y = startingCell.mid_point.coordinates.y();
        position = { x, y };
        drawPosition = { position[0] - food_half_size, position[1] - food_half_size };
        food_cell = startingCell;
    }*/

    /*void Food::generate_food(Cell (&board)[Cell::board_width][Cell::board_height])
        {
            int x = rand() % (Cell::board_width - 2) + 1;
            int y = rand() % (Cell::board_height - 2) + 1;

            //Solo spawnea la comida en sitios donde no esté la serpiente
            while (board[x][y].status != FREE)
            {
                if (++x == Cell::board_width)
                {
                    x = 0;
                    if (++y == Cell::board_height)
                    {
                        y = 0;
                    }
                }
            }

            food_cell = board[x][y];
            position = food_cell.mid_point;
            drawPosition = { position[0] - food_half_size, position[1] - food_half_size };
        }*/

    /*Vector2f Food::get_position()
    {
        return position;
    }*/

    /*void Food::draw_food(Canvas &canvas)
    {
        drawPosition = { position[0] - food_half_size, position[1] - food_half_size };
        canvas.set_color(1, 0, 0);
        canvas.fill_rectangle(drawPosition, { food_size, food_size });
    }*/

    /*int Food::random (int min, int max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<int> dist(min, max);

        return dist(mt);
    }*/
}
