/*
 * SAMPLE SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "Sample_Scene.hpp"
#include <basics/Director>
#include <basics/Log>
#include <basics/Scaling>
#include <basics/Rotation>
#include <basics/Translation>

using namespace basics;
using namespace std;

namespace snake
{
    constexpr float Cell::size;
    constexpr float Cell::half_size;

    Sample_Scene::Sample_Scene()
    {
        canvas_width  = 1280;
        canvas_height =  720;



        aspect_ratio_adjusted = false;
    }

    bool Sample_Scene::initialize ()
    {
        state     = LOADING;
        suspended = false;

        return true;
    }

    void Sample_Scene::suspend ()
    {
        suspended = true;
    }

    void Sample_Scene::resume ()
    {
        suspended = false;
    }

    void Sample_Scene::handle (Event & event)
    {
        /*if (state == RUNNING)
        {
            switch (event.id)
            {
                case ID(touch-started):
                case ID(touch-moved):
                case ID(touch-ended):
                {
                    x = *event[ID(x)].as< var::Float > ();
                    y = *event[ID(y)].as< var::Float > ();
                    break;
                }
            }
        }*/
    }

    void Sample_Scene::update (float time)
    {
        switch (state)
        {
            case LOADING: load ();     break;
            case RUNNING: run  (time); break;
        }
    }

    void Sample_Scene::render (basics::Graphics_Context::Accessor & context)
    {
        if (!suspended && state == RUNNING)
        {
            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

            if (!canvas)
            {
                canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
            }

            if (canvas)
            {
                canvas->clear();


                draw_cells(canvas);
                snake.draw_snake(canvas);

            }
        }
    }

    void Sample_Scene::load ()
    {
        if (!suspended)
        {
            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {
                
                if (!aspect_ratio_adjusted)
                {
                    // En este ejemplo la ventana está bloqueada para permanecer horizontal.
                    // Por tanto, lo normal es que el ancho sea mayor que el alto. El alto de la resolución
                    // virtual se va a dejar fijo en 720 unidades (tal como se estableció en el constructor)
                    // y se va a escalar el ancho de la resolución virtual para que el aspect ratio virtual
                    // coincida con el real de la ventana:

                    float real_aspect_ratio = float( context->get_surface_width () ) / context->get_surface_height ();

                    canvas_width = unsigned( canvas_height * real_aspect_ratio );

                    aspect_ratio_adjusted = true;

                    state = RUNNING;

                    create_cells();
                }




            }
        }
    }

    void Sample_Scene::run (float time)
    {
        snake.move(time);
    }

    void Sample_Scene::create_cells()
    {
        //Cells start points
        int offset_x = 0, offset_y = 0;
        for (int i = 0; i < board_height; ++i)
        {
            //Each row
            //v_cells.push_back(std::vector<Cell>());
            for (int j = 0; j < board_width; ++j)
            {
                //Each column
                //Cell new_cell;
                if((j == board_width - 2 || j == board_width - 1) || (i == 0 || i == board_height - 1))
                {
                    cells[i][j] = Cell(offset_x, offset_y, OCCUPIED);
                }
                else
                {
                    cells[i][j] = Cell(offset_x, offset_y, FREE);
                }

                offset_y += Cell::size;
            }
            offset_y = 0;

            offset_x += Cell::size;
        }
    }

    void Sample_Scene::draw_cells(Canvas * canvas)
    {
        int num_cells = 0;

        for (int i = 0; i < board_height; ++i)
        {
            //Each row
            //condition for correct tiling
            if(i % 2)
                num_cells = 0;
            else
                num_cells = 1;

            for (int j = 0; j < board_width; ++j) {
                num_cells++;

                //Each column
                canvas->fill_rectangle( cells[i][j].position , {cells[i][j].size, cells[i][j].size});


                if(cells[i][j].status == OCCUPIED)
                {
                    canvas->set_color(0.21f, 0.53f, 0); //55, 136, 5
                }
                else
                {
                    if(num_cells % 2 == 0)
                        canvas->set_color(0.6f, 0.95f, 0.3f); //55, 136, 5
                    else
                        canvas->set_color(0.53f, 0.86f, 0.24f); //134, 220, 61
                }



            }

        }
    }

}
