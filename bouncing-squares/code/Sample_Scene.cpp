/*
 * SAMPLE SCENE
 * Copyright © 2021 Miguel Gutierrez
 */

#include "Sample_Scene.hpp"
#include <basics/Accelerometer>
#include <basics/Canvas>
#include <basics/Director>
#include <iostream>


using namespace basics;
using namespace std;

namespace example
{

    void Sample_Scene::suspend ()
    {
        suspended = true;

    }

    void Sample_Scene::resume ()
    {
        suspended = false;

    }

    void Sample_Scene::update (float time)
    {

        if(delay > 0)
            delay -= time;


        
        square1.squareUpdate(time, canvas_width, canvas_height);

        square2.squareUpdate(time, canvas_width, canvas_height);

        if(distance(square1.x, square2.x, square1.y, square2.y) < square1.get_size()) {
            if(delay <= 0)
            {
                for (int i = 0; i < colorArray.size(); ++i) {
                    colorArray[i] = random(0.f, 1.f);
                }
                delay = 1.f;
            }

        }

    }

    void Sample_Scene::render (basics::Graphics_Context::Accessor & context)
    {
        if (!suspended)
        {
            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

            if (!canvas)
            {
                canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
            }

            if (canvas)
            {
                canvas->clear ();

                canvas->set_color (colorArray[0], colorArray[1], colorArray[2]);

                canvas->fill_rectangle({ square1.x - square1.get_half_size(), square1.y - square1.get_half_size() },
                                       { square1.get_size(), square1.get_size() });

                canvas->fill_rectangle({ square2.x - square1.get_half_size(), square2.y - square1.get_half_size() },
                                       { square1.get_size(), square1.get_size() });


            }
        }
    }

    float Sample_Scene::distance(float x1, float x2, float y1, float y2)
    {
        float dist;

        dist = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

        return dist;

    }

}
