/*
 * SNAKE
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#include "snake.h"


using namespace basics;

namespace snake
{


    void Snake::move(float deltaTime, vector<Pivot> & pivots)
    {
        if(direction == 0)
        {
            //mueve la serpiente hacia arriba
            x -= speed * deltaTime;
        }
        else if(direction == 1)
        {
            //mueve la serpiente hacia la izquierda
            y -= speed * deltaTime;
        }
        else if(direction == 2)
        {
            //mueve la serpiente hacia abajo
            x += speed * deltaTime;
        }
        else if(direction == 3)
        {
            //mueve la serpiente hacia la derecha
            y += speed * deltaTime;
        }
        else { }

        //Reestablece la posicion en la que se tiene que pintar la serpiente
        drawPosition = { x - snake_half_size, y - snake_half_size };

        //Movimiento del cuerpo
        for (int i = 0; i < sb.size(); ++i)
        {
            //Si es el primer elemento sigue a la cabeza
            //en caso contrario sigue al nodo anterior
            if(i != 0)
                sb[i].sb_move(deltaTime, { sb[i-1].sb_x, sb[i-1].sb_y }, sb[i-1].sb_direction);
            else
                sb[i].sb_move(deltaTime, { x, y }, direction);

            for (int j = 0; j < pivots.size(); ++j)
            {
                //Detección de cuando está cerca de un pivote para cambiar de posición
                if(helper::distance(pivots[j].position, { sb[i].sb_x, sb[i].sb_y } ) < snake_half_size)
                {
                    //CORRECCION VISUAL
                    //Esta condicion sirve para volver el objeto invisible en caso de que se vaya
                    //a salir de la casilla en la que se produce el giro
                    if(((sb[i].sb_direction == 0 && sb[i].sb_x < sb[i].sb_current_cell.mid_point[0]) ||
                    (sb[i].sb_direction == 1 && sb[i].sb_y < sb[i].sb_current_cell.mid_point[1]) ||
                    (sb[i].sb_direction == 2 && sb[i].sb_x > sb[i].sb_current_cell.mid_point[0]) ||
                    (sb[i].sb_direction == 3 && sb[i].sb_y > sb[i].sb_current_cell.mid_point[1]))
                    && sb[i].sb_current_cell.position == pivots[j].pivot_cell.position)
                        sb[i].timerVisible.reset();

                    //Cambia la direccion del objeto al sobrepasar el pivote
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

                        //Borra el ultimo pivote cuando el final de la serpiente pasa por
                        //el mismo
                        if(sb[i].sb_x == sb.back().sb_x && sb[i].sb_y == sb.back().sb_y
                           && pivots[j].position == pivots.front().position)
                        {
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
            //Cada fila
            for (int j = 0; j < Cell::board_height; ++j) {
                //Cada columna

                //En caso de que no sean bordes: resetea los estados de las celdas a libres
                if((j == 0 || j == Cell::board_height - 1) || (i == 0 || i == Cell::board_width - 1)) { }
                else
                    board[i][j].status = FREE;

                //Recorre el vector del cuerpo, en caso de que alguna casilla contenga un elemento
                //la pone en ocupada
                for (int k = 0; k < sb.size(); ++k) {
                    if(board[i][j].contains( { sb[k].sb_x, sb[k].sb_y } ))
                    {
                        sb[k].sb_current_cell = board[i][j];
                        board[i][j].status = OCCUPIED;

                    }
                }

                //Si contiene a la serpiente la pone en ocupada también
                if(board[i][j].contains( { x, y } ))
                {

                    current_cell = board[i][j];
                    board[i][j].status = OCCUPIED;

                }

            }

        }
    }

    void Snake::check_food_collision(Food & food, Cell (&board)[Cell::board_width][Cell::board_height])
    {
        //Calcula la distancia entre la posicion de la serpiente y la comida
        //si es menor a un umbral, la comida cambia de lado y se amplia la serpiente
        if(helper::distance( { x, y }, food.get_position()) < (snake_half_size + food.food_half_size) - 20)
        {
            food.generate_food(board);

            sb.emplace_back(
                    snake_body({sb.back().sb_x, sb.back().sb_y}, sb.back().sb_direction)
            );
        }
    }

    bool Snake::check_endgame_collision()
    {
        //Si está en un borde
        if(current_cell.status == BORDER)
        {
            direction = -1;
            return true;
        }

        //Si se choca consigo misma
        for (int i = 0; i < sb.size(); ++i) {
            if(i != 0 && i != 1)
            {
                if(sb[i].contains( { x, y } ))
                {
                    direction = -1;
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




