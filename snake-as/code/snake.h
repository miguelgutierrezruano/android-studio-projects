//
// Created by migue on 19/01/2022.
//

#include "cell.h"
#include "Food.h"
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

        struct snake_body
        {
            float sb_x, sb_y;
            float sb_speed;
            float sb_direction;
            Cell sb_current_cell;
            Vector2f sb_drawPosition;

            snake_body()
            {
                sb_x = 300;
                sb_y = 300;
                sb_speed = 300;
                sb_direction = -1;
                sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
            }
            snake_body(Cell sb_starting_cell)
            {
                sb_x = sb_starting_cell.mid_point.coordinates.x();
                sb_y = sb_starting_cell.mid_point.coordinates.y();
                sb_speed = 300;
                sb_direction = -1;
                sb_drawPosition = { sb_x - snake_half_size, sb_y - snake_half_size };
                sb_current_cell = sb_starting_cell;
            }

            void draw_snake_body(Canvas & canvas)
            {
                canvas.set_color(0.26f, 0.6f, 0.97f);
                canvas.fill_rectangle(sb_drawPosition, { snake_size, snake_size });
            }

            float sb_distance(Vector2f p1, Vector2f p2)
            {
                float dist;

                dist = sqrt(((p2[0] - p1[0]) * (p2[0] - p1[0])) + ((p2[1] - p1[1]) * (p2[1] - p1[1])));

                return dist;
            }

            void sb_move(float deltaTime, Vector2f followed_position, float node_direction)
            {
                if((sb_direction == 1 || sb_direction == 3) && abs(sb_y - followed_position[1]) < 5)
                {
                    //el nodo anterior esta en horizontal
                    if(sb_x - followed_position.coordinates.x() < 0)
                    {
                        //x tiene que disminuir
                        sb_direction = 2;
                        sb_y = followed_position[1];
                    }
                    else
                    {
                        sb_direction = 0;
                        sb_y = followed_position[1];
                    }

                }
                else if((sb_direction == 0 || sb_direction == 2) && abs(sb_x - followed_position[0]) < 5)
                {
                    //el nodo anterior esta en vertical
                    if(sb_y - followed_position.coordinates.y() < 0)
                    {
                        //y tiene que disminuir
                        sb_direction = 3;
                        sb_x = followed_position[0];
                    }
                    else
                    {
                        sb_direction = 1;
                        sb_x = followed_position[0];
                    }

                }


                if(node_direction == sb_direction && sb_distance( {sb_x, sb_y}, followed_position) < snake_size + 5) { }
                else if(sb_direction == 0)
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
            }
            void calculate_sb_current_cell(Cell board[Cell::board_width][Cell::board_height])
            {
                for (int i = 0; i < Cell::board_width; ++i)
                {
                    //Each row

                    for (int j = 0; j < Cell::board_height; ++j) {

                        if(board[i][j].contains( { sb_x, sb_y } ))
                        {

                            sb_current_cell = board[i][j];
                        }


                    }

                }

                //sb_current_cell.status = OCCUPIED;
            }

        };

        Cell current_cell;
        snake_body sb;
    private:
        float x, y;
        float speed;
        float direction;
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

        void grow() { lenght++; }

        void draw_snake(Canvas & canvas)
        {
            canvas.set_color(0.26f, 0.6f, 0.97f);
            canvas.fill_rectangle(drawPosition, { snake_size, snake_size });
            //draw body
            sb.draw_snake_body(canvas);
        }
        void move(float deltaTime);

        void calculate_current_cell(Cell board[Cell::board_width][Cell::board_height]);
        void check_food_collision(Food & food, Cell board[Cell::board_width][Cell::board_height]);
        float distance(Vector2f p1, Vector2f p2);

        void change_direction(int , float &);

        void game_over()
        {
            direction = -1;
        }
    };
}





