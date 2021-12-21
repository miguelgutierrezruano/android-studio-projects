//
// Created by migue on 11/12/2021.
//

//#ifndef BASICS_ACCELEROMETER_EXAMPLE_SQUARE_H
//#define BASICS_ACCELEROMETER_EXAMPLE_SQUARE_H

namespace example
{
    class Square {

    private:
        float    square_size;
        float    half_size;


        float    speed;
        bool     changeX;
        bool     changeY;

    public:
        float    x;
        float    y;

        Square()
        {
            square_size   =   60;
            half_size     =   square_size / 2;
            speed         =   500;
        }

        void squareUpdate(float time, unsigned int canvas_w, unsigned int canvas_h);

        //float get_x() { return x; };
        //float get_y() { return y; };
        float get_size() { return square_size; }
        float get_half_size() { return half_size; }

    };
}




//#endif //BASICS_ACCELEROMETER_EXAMPLE_SQUARE_H
