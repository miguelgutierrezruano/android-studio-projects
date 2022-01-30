/*
 * SNAKE_BODY
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

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
    /**
         * Cada objeto de este tipo es un componente más del cuerpo de la serpiente
         */

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
            sb_speed = 350;
            sb_direction = -1;
            sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            isVisible = true;
        }

        /**
         * Constructor para iniciar el primer elemento del cuerpo
         * @param sb_starting_cell la celda en la que empieza
         */
        snake_body(Cell sb_starting_cell)
        {
            sb_x = sb_starting_cell.mid_point.coordinates.x();
            sb_y = sb_starting_cell.mid_point.coordinates.y();
            sb_speed = 350;
            sb_direction = -1;
            sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            sb_current_cell = sb_starting_cell;
            isVisible = true;
        }

        /**
         * Constructor para añadir nuevos elementos
         * @param pos la posicion inicial
         * @param starting_direction la direccion inicial
         */
        snake_body(Vector2f pos, float starting_direction)
        {
            sb_x = pos[0];
            sb_y = pos[1];
            sb_speed = 0;
            sb_direction = starting_direction;
            sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            isVisible = true;
        }

        /**
         * Método que pinta en el canvas el objeto
         * @param canvas el canvas que se está usando
         */
        void draw_snake_body(Canvas & canvas)
        {
            canvas.set_color(0.26f, 0.6f, 0.97f);
            canvas.fill_rectangle(sb_drawPosition, { snake_size, snake_size });
        }

        /**
         * Este método mueve el cuerpo de la serpiente según su dirección
         * @param deltaTime tiempo entre frame y frame
         * @param followed_position posicion del nodo anterior
         * @param node_direction direccion del nodo anterior
         */
        void sb_move(float deltaTime, Vector2f followed_position, int node_direction)
        {
            //En caso de que el cuerpo este este muy cerca de la posicion a seguir
            //se reduce la velocidad
            if(node_direction == sb_direction &&
               helper::distance( {sb_x, sb_y}, followed_position) < snake_size)
            {
                sb_speed = 50;
            }
            //En caso de que el cuerpo este este muy lejos de la posicion a seguir
            //aumenta la velocidad
            else if(node_direction == sb_direction &&
                     helper::distance( {sb_x, sb_y}, followed_position) > snake_size + 5)
            {
                sb_speed = 400;
            }
            else { sb_speed = 350; }

            //Mueve la serpiente en función de su dirección
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

            //CORRECCION VISUAL
            //Se resetea si se va a salir, espera 2 centesimas de segundo
            //(para que ya no esté salida) y la vuelve a poner visible
            if(timerVisible.get_elapsed_seconds() > 0.02f)
                isVisible = true;
            else
                isVisible = false;
        }

        /**
         * Este método cambia la dirección
         * @param _direction direccion deseada
         */
        void sb_change_direction(int _direction)
        {
            sb_direction = _direction;
        }

        /**
         * Este método señala si el objeto contiene un punto dado
         * @return true si el punto esta dentro, false si esta fuera
         * @param point, punto a comprobar
         */
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

