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
    constexpr unsigned Cell::board_width;
    constexpr unsigned Cell::board_height;
    constexpr float Cell::size;
    constexpr float Cell::half_size;

    Sample_Scene::Sample_Scene()
    {
        canvas_width  = 1280;
        canvas_height =  720;

        start_point = 0;
        last_point = 0;
        state = LOADING;
        suspended = false;
        delay = 0;
        first_touch = true;
        touched_controller = nullptr;

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
        if (state == RUNNING && !suspended)
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
                                touched_controller->color = { 0.06f, 0.29f, 0.51f };

                                if(first_touch)
                                {
                                    if(i != 1)
                                    {
                                        snake.change_direction(i, delay);
                                        snake.sb[0].sb_direction = 3;
                                        pivot_list.emplace_back(
                                                Pivot(snake.current_cell.mid_point, snake.get_dir())
                                                );
                                        first_touch = false;
                                    }

                                }
                                else
                                {
                                    if(delay <= 0)
                                    {
                                        snake.change_direction(i, delay);
                                        pivot_list.emplace_back(
                                                Pivot(snake.current_cell.mid_point, snake.get_dir())
                                        );

                                    }
                                }

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
                        touched_controller->color = { 0.26f, 0.6f, 0.97f };

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
                food.draw_food(*canvas);

                //for (int i = 0; i < pivot_list.size(); ++i) {
                //    canvas->set_color(1, 0,0);
                //    canvas->fill_rectangle(pivot_list[i].position, {5, 5});
                //}

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

                    first_touch = true;

                    create_cells();
                    create_controllers();

                    snake = Snake(cells[Cell::board_width/2][Cell::board_height/3]);
                    snake.sb.emplace_back(
                            snake_body(cells[Cell::board_width/2][Cell::board_height/3 - 1])
                            );
                    snake.calculate_current_cell(cells);
                    food = Food(cells[Cell::board_width/2][(Cell::board_height/3) * 2 + 1]);

                    delay = 0.f;

                    state = RUNNING;

                }




            }
        }
    }

    void Sample_Scene::run (float time)
    {
        snake.calculate_current_cell(cells);
        snake.move(time, pivot_list);
        snake.check_food_collision(food, cells);

        if(delay > 0)
        {
            delay -= time;
        }

    }

    void Sample_Scene::create_cells()
    {
        //Cells start points
        float offset_x = 0, offset_y = start_point;
        for (int i = 0; i < Cell::board_width; ++i)
        {
            //Each row (vertical)
            //v_cells.push_back(std::vector<Cell>());
            for (int j = 0; j < Cell::board_height; ++j)
            {
                //Each column (vertical)
                //Cell new_cell;
                if((j == 0 || j == Cell::board_height - 1) || (i == 0 || i == Cell::board_width - 1))
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
        int num_cells;

        for (int i = 0; i < Cell::board_width; ++i)
        {
            //Each row
            //condition for correct tiling
            if(i % 2)
                num_cells = 0;
            else
                num_cells = 1;

            for (int j = 0; j < Cell::board_height; ++j) {
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
        start_point = (canvas_height - (Cell::board_height * Cell::size)) * 0.5f;
        last_point = canvas_height - start_point;

        float free_size = canvas_width - Cell::board_width * Cell::size;
        float midpoint_x = canvas_width - (free_size * 0.5f);
        midpoint = { midpoint_x, (last_point + start_point) * 0.5f  };

    }

    void Sample_Scene::create_controllers()
    {
        float offset = 5;

        controllers.emplace_back
        (
                new Controller({ Cell::board_width * Cell::size, start_point + offset },
                               { Cell::board_width * Cell::size, last_point - offset },
                               { midpoint.coordinates.x() - offset, midpoint.coordinates.y() },
                               { 0.26f, 0.6f, 0.97f })
                );
        controllers.emplace_back(
                new Controller({ Cell::board_width * Cell::size + offset, start_point },
                               { canvas_width - offset, start_point },
                               { midpoint.coordinates.x(), midpoint.coordinates.y() - offset },
                               {0.26f, 0.6f, 0.97f})
                );
        controllers.emplace_back(
                new Controller({ canvas_width, start_point + offset },
                               { canvas_width, last_point - offset },
                               { midpoint.coordinates.x() + offset, midpoint.coordinates.y() },
                               { 0.26f, 0.6f, 0.97f })
                );
        controllers.emplace_back(
                new Controller({ Cell::board_width * Cell::size + offset, last_point  },
                               { canvas_width - offset, last_point },
                               { midpoint.coordinates.x(), midpoint.coordinates.y() + offset },
                               { 0.26f, 0.6f, 0.97f })
                );


    }

}
