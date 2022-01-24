//
// Created by migue on 23/01/2022.
//

//#ifndef SNAKE_PROTOTYPE_FOOD_H
//#define SNAKE_PROTOTYPE_FOOD_H

#pragma once

#include "cell.h"
#include <basics/Vector>
#include <basics/Canvas>
#include <iostream>
#include <random>

using namespace basics;
using namespace std;

namespace snake
{

    class Food {

    public:
        static constexpr float food_size = 40;
        static constexpr float food_half_size = food_size / 2;

        Cell food_cell;

    private:
        int x, y;
        Vector2f drawPosition;
        Vector2f position;

    public:
        Food() { }

        Food(Cell startingCell)
        {
            x = startingCell.mid_point.coordinates.x();
            y = startingCell.mid_point.coordinates.y();
            position = { x, y };
            drawPosition = { position[0] - food_half_size, position[1] - food_half_size };
            food_cell = startingCell;
        }


        int random(int min, int max)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<unsigned int> dist(min, max);

            return dist(mt);
        }



        void generate_food(Cell board[Cell::board_width][Cell::board_height])
        {
            x = rand() % (Cell::board_width - 2) + 1;
            y = rand() % (Cell::board_height - 2) + 1; //random(1, Cell::board_height - 1)

            while (board[x][y].status == OCCUPIED)
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
        }

        void draw_food(Canvas & canvas)
        {
            //drawPosition = { position[0] - food_half_size, position[1] - food_half_size };
            canvas.set_color(1, 0, 0);
            canvas.fill_rectangle(drawPosition, { food_size, food_size });
        }


        Vector2f get_position() { return position; }

    };
}

//#endif //SNAKE_PROTOTYPE_FOOD_H
