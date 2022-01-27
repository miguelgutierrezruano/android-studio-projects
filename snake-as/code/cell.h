//
// Created by migue on 15/01/2022.
//

#pragma once

#include <basics/Vector>


namespace snake
{
    enum CellStatus {
        FREE,
        OCCUPIED,
        BORDER
    };

    struct Cell {

    private:


    public:
        static constexpr unsigned board_width = 17;
        static constexpr unsigned board_height = 14;
        static constexpr float size = 50;
        static constexpr float half_size = size / 2;


        basics::Vector2f position;
        basics::Vector2f mid_point;

        CellStatus status;
        bool hasPivot;



    public:
        Cell()
        {

            position = { 0, 0 };
            status = FREE;
            mid_point = { position.coordinates.x() + half_size, position.coordinates.y() + half_size };
        }
        //Cell() { };

        Cell(float _x, float _y, CellStatus _status)
        {
            position = { _x, _y };
            status = _status;
            mid_point = { position.coordinates.x() + half_size, position.coordinates.y() + half_size };
        }

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

        Pivot() { }
        Pivot(basics::Vector2f pos, int dir, Cell & _pivotcell)
        {
            position = pos;
            turn_direction = dir;
            pivot_cell = _pivotcell;
        }
    };
}



