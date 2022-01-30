/*
 * FOOD
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#include "cell.h"
#include <basics/Vector>
#include <basics/Canvas>
#include <iostream>
#include <random>

using namespace basics;
using namespace std;

namespace snake
{

    /**
         * Clase para representar la comida
         */
    class Food {

    public:
        static constexpr float food_size = 40;
        static constexpr float food_half_size = food_size / 2;

        Cell food_cell;

    private:
        //int x, y;
        Vector2f drawPosition;
        Vector2f position;

    public:
        Food() { }

        /**
         * Constructor que inicializa el objeto en una celda
         * @param startingCell, celda en la que iniciar
         */
        Food(Cell startingCell)
        {
            position = { startingCell.mid_point.coordinates.x(), startingCell.mid_point.coordinates.y() };
            drawPosition = { position[0] - food_half_size, position[1] - food_half_size };
            food_cell = startingCell;
        }


        /**
         * Este método mueve la fruta de sitio (genera otra)
         * @param board, array bidimensional de casillas
         */
        void generate_food(Cell (&board)[Cell::board_width][Cell::board_height])
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
        }

        /**
         * Este método pinta la comida en el canvas
         * @param canvas, canvas actual del juego
         */
        void draw_food(Canvas & canvas)
        {
            //drawPosition = { position[0] - food_half_size, position[1] - food_half_size };
            canvas.set_color(1, 0, 0);
            canvas.fill_rectangle(drawPosition, { food_size, food_size });
        }


        Vector2f get_position() { return position; }

    };
}

