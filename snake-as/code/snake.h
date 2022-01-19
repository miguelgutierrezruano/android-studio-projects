//
// Created by migue on 19/01/2022.
//

#include <basics/Vector>
#include <basics/Canvas>

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
            speed = 500;
            direction = 0;
            drawPosition = { x - snake_half_size, y - snake_half_size };
        }
        void draw_snake(Canvas* canvas)
        {
            canvas->fill_rectangle(drawPosition, { snake_size, snake_size });
            //canvas->set_color(0, 0, 1);

        }
        void move(float deltaTime)
        {
            if(direction == 0)
            {
                x += speed * deltaTime;
            }
            else if(direction == 1)
            {
                x -= speed * deltaTime;
            }
            else if(direction == 2)
            {
                y += speed * deltaTime;
            }
            else if(direction == 3)
            {
                y -= speed * deltaTime;
            }
            else { }

            drawPosition = { x - snake_half_size, y - snake_half_size };

        }
        void change_direction(float );

    };
}





