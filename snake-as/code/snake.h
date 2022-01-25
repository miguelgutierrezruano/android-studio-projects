//
// Created by migue on 19/01/2022.
//

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
        int lenght;

        //vector<snake_body> v_snake_body;

        Vector2f drawPosition;


    public:
        Snake()
        {
            x = 300;
            y = 300;
            speed = 300;
            direction = -1;
            lenght = 1;
            drawPosition = { x - snake_half_size, y - snake_half_size };

        }

        Snake(Cell startingCell)
        {
            x = startingCell.mid_point.coordinates.x();
            y = startingCell.mid_point.coordinates.y();
            speed = 300;
            direction = -1;
            lenght = 1;
            //v_snake_body.emplace_back();
            drawPosition = { x - snake_half_size, y - snake_half_size };
            current_cell = startingCell;

        }

        //void grow() { lenght++; }

        void draw_snake(Canvas & canvas)
        {
            canvas.set_color(0.26f, 0.6f, 0.97f);
            canvas.fill_rectangle(drawPosition, { snake_size, snake_size });
            //draw body

            if(!sb.empty())
            {
                for (int i = 0; i < sb.size(); ++i) {
                    sb[i].draw_snake_body(canvas);
                }
            }


        }
        void move(float deltaTime, vector<Pivot> & pivots);

        void calculate_current_cell(Cell (&board)[Cell::board_width][Cell::board_height]);
        void check_food_collision(Food & food, Cell board[Cell::board_width][Cell::board_height]);

        void change_direction(int , float &);

        int get_dir() { return direction; }

        void game_over()
        {
            sb.clear();
            direction = -1;
        }
    };
}





