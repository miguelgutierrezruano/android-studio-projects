//
// Created by migue on 11/12/2021.
//

#include "Square.h"

namespace example
{
    void Square::squareUpdate(float time, unsigned int canvas_w, unsigned int canvas_h)
    {
        //float roll  = 50;
        //float pitch = 50;

        if(changeX)
            x += speed * time;
        else
            x -= speed * time;

        if(changeY)
            y += speed * time;
        else
            y -= speed * time;

        if (x - half_size <  0.f)
            changeX = true;
        else if(x + half_size >= canvas_w)
            changeX = false;


        if (y - half_size <  0.f)
            changeY = true;
        else if(y + half_size >= canvas_h)
            changeY = false;
    }


}

