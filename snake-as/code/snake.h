//
// Created by migue on 19/01/2022.
//

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
        void draw_snake(Canvas & canvas)
        {
            canvas.set_color(0, 0, 1);
            canvas.fill_rectangle(drawPosition, { snake_size, snake_size });


        }
        void move(float deltaTime);


        void change_direction(int );

    };
}





