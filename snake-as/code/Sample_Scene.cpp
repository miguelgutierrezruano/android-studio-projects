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
        if (state == RUNNING)
        {
            switch (event.id)
            {
                case ID(touch-started):
                {
                    if(!touched_controller)
                    {
                        touch_location =
                                {
                                        *event[ID(x)].as< var::Float > (),
                                        *event[ID(y)].as< var::Float > ()
                                };

                        for (int i = 0; i < controllers.size(); ++i)
                        {
                            if(controllers[i]->contains(touch_location))
                            {
                                touched_controller = controllers[i].get();
                                touched_controller->color = { 0.65f, 0.38f, 0.08f };
                                snake.change_direction(i);
                                //move snake
                                break;
                            }
                        }
                    }


                    break;
                }

                case ID(touch-moved):
                {
                    if(touched_controller)
                    {
                        touch_location =
                                {
                                        *event[ID(x)].as< var::Float > (),
                                        *event[ID(y)].as< var::Float > ()
                                };
                    }
                    break;
                }
                case ID(touch-ended):
                {
                    if(touched_controller)
                    {
                        touch_location =
                                {
                                        *event[ID(x)].as< var::Float > (),
                                        *event[ID(y)].as< var::Float > ()
                                };
                        touched_controller->color = { 1, 0.61f, 0.17f };

                        touched_controller = nullptr;
                    }
                    break;
                }
            }
        }
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


                draw_cells(*canvas);
                snake.draw_snake(*canvas);

                for (int i = 0; i < controllers.size(); ++i) {
                    controllers[i]->render(*canvas);
                }
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
                    float real_aspect_ratio = float( context->get_surface_width () ) / context->get_surface_height ();

                    canvas_width = unsigned( canvas_height * real_aspect_ratio );

                    aspect_ratio_adjusted = true;

                    calculate_start_point();

                    create_cells();
                    create_controllers();

                    snake = Snake(cells[5][5]);
                    snake.calculate_current_cell(cells);

                    state = RUNNING;





                }




            }
        }
    }

    void Sample_Scene::run (float time)
    {
        snake.calculate_current_cell(cells);
        snake.move(time);
    }

    void Sample_Scene::create_cells()
    {
        //Cells start points
        float offset_x = 0, offset_y = start_point;
        for (int i = 0; i < board_width; ++i)
        {
            //Each row (vertical)
            //v_cells.push_back(std::vector<Cell>());
            for (int j = 0; j < board_height; ++j)
            {
                //Each column (vertical)
                //Cell new_cell;
                if((j == 0 || j == board_height - 1) || (i == 0 || i == board_width - 1))
                {
                    cells[i][j] = Cell(offset_x, offset_y, OCCUPIED);
                }
                else
                {
                    cells[i][j] = Cell(offset_x, offset_y, FREE);
                }

                offset_y += Cell::size;
            }
            offset_y = start_point;

            offset_x += Cell::size;
        }
    }

    void Sample_Scene::draw_cells(Canvas & canvas)
    {
        int num_cells = 0;

        for (int i = 0; i < board_width; ++i)
        {
            //Each row
            //condition for correct tiling
            if(i % 2)
                num_cells = 0;
            else
                num_cells = 1;

            for (int j = 0; j < board_height; ++j) {
                num_cells++;

                if(cells[i][j].status == OCCUPIED)
                {
                    canvas.set_color(0.21f, 0.53f, 0); //55, 136, 5
                }
                else
                {
                    if(num_cells % 2 == 0)
                        canvas.set_color(0.6f, 0.95f, 0.3f); //55, 136, 5
                    else
                        canvas.set_color(0.53f, 0.86f, 0.24f); //134, 220, 61
                }

                //Each column
                canvas.fill_rectangle( cells[i][j].position , {cells[i][j].size, cells[i][j].size});

                //canvas.set_color(1, 0,0);
                //canvas.fill_rectangle( snake.current_cell.position, {cells[i][j].size, cells[i][j].size} );




            }

        }

    }

    void Sample_Scene::calculate_start_point()
    {
        start_point = (canvas_height - (board_height * Cell::size)) * 0.5f;
        last_point = canvas_height - start_point;

        float free_size = canvas_width - board_width * Cell::size;
        float midpoint_x = canvas_width - (free_size * 0.5f);
        midpoint = { midpoint_x, (last_point + start_point) * 0.5f  };

    }

    void Sample_Scene::create_controllers()
    {
        float offset = 5;

        controllers.emplace_back
        (
                new Controller({ board_width * Cell::size, start_point + offset },
                               { board_width * Cell::size, last_point - offset },
                               { midpoint.coordinates.x() - offset, midpoint.coordinates.y() },
                               { 1, 0.61f, 0.17f })
                );
        controllers.emplace_back(
                new Controller({ board_width * Cell::size + offset, start_point },
                               { canvas_width - offset, start_point },
                               { midpoint.coordinates.x(), midpoint.coordinates.y() - offset },
                               { 1, 0.61f, 0.17f })
                );
        controllers.emplace_back(
                new Controller({ canvas_width, start_point + offset },
                               { canvas_width, last_point - offset },
                               { midpoint.coordinates.x() + offset, midpoint.coordinates.y() },
                               { 1, 0.61f, 0.17f })
                );
        controllers.emplace_back(
                new Controller({ board_width * Cell::size + offset, last_point  },
                               { canvas_width - offset, last_point },
                               { midpoint.coordinates.x(), midpoint.coordinates.y() + offset },
                               { 1, 0.61f, 0.17f })
                );


    }

}
