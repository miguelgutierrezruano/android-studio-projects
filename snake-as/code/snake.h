//
// Created by migue on 19/01/2022.
//

#include "cell.h"
#include <basics/Vector>
#include <basics/Canvas>
#include <iostream>

using namespace basics;
using namespace std;

namespace snake
{
    class Snake {

    public:
        static constexpr float snake_size = 40;
        static constexpr float snake_half_size = snake_size / 2;

        static constexpr int board_swidth = 17;
        static constexpr int board_sheight = 14;

        Cell current_cell;

    private:
        float x, y;
        float speed;
        float direction;
        Vector2f drawPosition;


    public:
        Snake()
        {
            x = 300;
            y = 300;
            speed = 300;
            direction = -1;
            drawPosition = { x - snake_half_size, y - snake_half_size };
        }

        Snake(Cell startingCell)
        {
            x = startingCell.mid_point.coordinates.x();
            y = startingCell.mid_point.coordinates.y();
            speed = 300;
            direction = -1;
            drawPosition = { x - snake_half_size, y - snake_half_size };
            current_cell = startingCell;
        }


        void draw_snake(Canvas & canvas)
        {
            canvas.set_color(0, 0, 1);
            canvas.fill_rectangle(drawPosition, { snake_size, snake_size });


        }
        void move(float deltaTime);

        void calculate_current_cell(Cell board[board_swidth][board_sheight]);


        void change_direction(int );

    };
}





