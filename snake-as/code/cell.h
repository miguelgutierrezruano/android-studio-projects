//
// Created by migue on 15/01/2022.
//

#pragma once

#include <basics/Vector>

namespace snake
{
    enum CellStatus {
        FREE,
        OCCUPIED
    };

    struct Cell {

    private:


    public:
        static constexpr float size = 50;
        static constexpr float half_size = size / 2;


        basics::Vector2f position;
        basics::Vector2f mid_point;

        CellStatus status;



    public:
        /*Cell()
        {

            position = { 0, 0 };
            status = FREE;
            mid_point = { position.coordinates.x() + half_size, position.coordinates.y() + half_size };
        }*/
        Cell() { };

        Cell(float _x, float _y, CellStatus _status)
        {
            position = { _x, _y };
            status = _status;
            mid_point = { position.coordinates.x() + half_size, position.coordinates.y() + half_size };
        }
    };
}



