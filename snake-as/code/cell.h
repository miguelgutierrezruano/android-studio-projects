/*
 * CELL
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#pragma once

#include <basics/Vector>


namespace snake
{
    ///enumeracion que determina el estado que puede tener una casilla
    enum CellStatus {
        FREE,
        OCCUPIED,
        BORDER
    };

    ///celdas por las que se moverá la serpiente
    struct Cell {

    private:


    public:
        static constexpr unsigned board_width = 16;
        static constexpr unsigned board_height = 14;
        static constexpr float size = 50;
        static constexpr float half_size = size / 2;


        basics::Vector2f position;
        basics::Vector2f mid_point;

        CellStatus status;



    public:
        ///constructor por defecto
        Cell()
        {

            position = { 0, 0 };
            status = FREE;
            mid_point = { position.coordinates.x() + half_size, position.coordinates.y() + half_size };
        }

        /**
         * Constructor que indica una posicion y un status
         * @param _x componente x de la posicion en la que debe estar
         * @param _y componente y de la posicion en la que debe estar
         * @param _status estado inicial de la casilla
         */
        Cell(float _x, float _y, CellStatus _status)
        {
            position = { _x, _y };
            status = _status;
            mid_point = { position.coordinates.x() + half_size, position.coordinates.y() + half_size };
        }

        /**
         * Este método comprueba si un punto está dentro de la casilla
         * @param point, punto a comprobar
         * @return true si el punto esta dentro, false si esta fuera
         */
        bool contains (const basics::Vector2f & point) const
        {
            return
                    point[0] > position[0] &&
                    point[1] > position[1] &&
                    point[0] < position[0] + size &&
                    point[1] < position[1] + size;
        }
    };

    struct Pivot
    {
        basics::Vector2f position;
        int turn_direction;
        Cell pivot_cell;

        ///Constructor por defecto
        Pivot() { }

        /**
         * Constructor que crea un pivote con una direccion una posicion
         * y esta contenido en una casilla
         * @param pos, posicion del pivote
         * @param dir, direccion a la que se tendra que cambiar pasado ese pivote
         * @param _pivotcell, celda que contiene el pivote
         */
        Pivot(basics::Vector2f pos, int dir, Cell & _pivotcell)
        {
            position = pos;
            turn_direction = dir;
            pivot_cell = _pivotcell;
        }
    };
}



