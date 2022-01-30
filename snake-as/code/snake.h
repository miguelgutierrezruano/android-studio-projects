/*
 * SNAKE
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#include "cell.h"
#include "Food.h"
#include "snake_body.h"
#include <basics/Vector>
#include <basics/Canvas>
#include <iostream>
#include <cmath>

using namespace basics;
using namespace std;

namespace snake
{


    class Snake {

    public:
        static constexpr float snake_size = 40;
        static constexpr float snake_half_size = snake_size / 2;


        Cell current_cell;
        vector<snake_body> sb;
    private:
        float x, y;
        float speed;
        int direction;

        Vector2f drawPosition;


    public:
        /**
         * Constructor por defecto
         */
        Snake()
        {
            x = 300;
            y = 300;
            speed = 350;
            direction = -1;
            drawPosition = { x - snake_half_size, y - snake_half_size };

        }

        /**
         * Constructor para crear la serpiente en una direccion concreta
         * @param startingCell celda inicial
         */
        Snake(Cell startingCell)
        {
            x = startingCell.mid_point.coordinates.x();
            y = startingCell.mid_point.coordinates.y();
            speed = 350;
            direction = -1;
            //v_snake_body.emplace_back();
            drawPosition = { x - snake_half_size, y - snake_half_size };
            current_cell = startingCell;

        }

        /**
         * Método que pinta la serpiente en el canvas
         * Pinta también el vector de snake_bodys
         * @param canvas el canvas que se está usando
         */
        void draw_snake(Canvas & canvas)
        {
            canvas.set_color(0.26f, 0.6f, 0.97f);
            canvas.fill_rectangle(drawPosition, { snake_size, snake_size });
            //draw body



            if(!sb.empty())
            {
                for (int i = 0; i < sb.size(); ++i) {
                    if(sb[i].isVisible)
                        sb[i].draw_snake_body(canvas);
                }
            }


        }

        /**
         * Método mueve toda la serpiente
         * Incluyendo el cuerpo
         * @param deltaTime, tiempo entre frame y frame
         * @param pivots, vector de todos los pivotes activos
         */
        void move(float deltaTime, vector<Pivot> & pivots);

        /**
         * Calcula en que casillas estám la serpiente y su cuerpo
         * Pone esas casillas ocupadas para que no puedan salir frutas
         * @param board, array bidimensional de celdas
         */
        void calculate_current_cell(Cell (&board)[Cell::board_width][Cell::board_height]);

        /**
         * Calcula la colisión con las frutas, en caso positivo amplía la serpiente
         * @param food, referencia al objeto food
         * @param board, array bidimensional de celdas
         */
        void check_food_collision(Food & food, Cell (&board)[Cell::board_width][Cell::board_height]);

        /**
         * Método que comprueba la colisión consigo misma y con la pared
         * @return true si ha colisionado false en caso negativo
         */
        bool check_endgame_collision();

        /**
         * Método que cambia la dirección de la serpiente
         */
        void change_direction(int);

        int get_dir() { return direction; }
        float get_x() { return x; }
        float get_y() { return y; }

    };
}





