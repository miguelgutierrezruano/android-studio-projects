/*
 * SAMPLE_SCENE
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
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
        //En caso de que esté pausado detectamos cualquier toque para volver al juego
        if(state == PAUSED && !suspended)
        {
            switch (event.id)
            {
                case ID(touch-started):
                {
                    touch_location =
                            {
                                    *event[ID(x)].as< var::Float > (),
                                    *event[ID(y)].as< var::Float > ()
                            };

                    break;
                }

                case ID(touch-moved):
                {
                    break;
                }
                case ID(touch-ended):
                {
                    //if(cells[0][0].contains(touch_location))
                        state = RUNNING;
                    break;
                }
            }
        }

        //Si el juego esta ejecutandose se comprueban los toques en los controladores
        //y en el botón de pausa para cambiar la posicion de la serpiente o pausar el juego
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

                                //First touch es controlado porque hay que darle un valor
                                //inicial a la dirección del body
                                if(first_touch)
                                {
                                    //No puede ir hacia su cuerpo
                                    if(i != 1)
                                    {
                                        //No reacciona ante cambios imposibles
                                        if(i == 0 && snake.get_dir() == 2) { }
                                        else if (i ==  2 && snake.get_dir() == 0) { }
                                        else if (i == 3 && snake.get_dir() == 1) { }
                                        else if (i == snake.get_dir()) { }
                                        else
                                        {
                                            //Inserta un pivote solo si en esa casilla no hay uno aún
                                            bool canSpawn = true;
                                            if(!pivot_list.empty())
                                            {
                                                for (int j = 0; j < pivot_list.size(); ++j) {
                                                    if(snake.current_cell.contains(pivot_list[i].position))
                                                        canSpawn = false;
                                                }

                                            }

                                            if(canSpawn)
                                            {
                                                pivot_list.emplace_back(
                                                        Pivot({ snake.get_x(), snake.get_y() }, i, snake.current_cell)
                                                );
                                                snake.change_direction(i);
                                                snake.sb[0].sb_direction = 3;
                                                first_touch = false;
                                            }

                                        }


                                    }

                                }
                                else
                                {
                                    //No reacciona ante cambios imposibles
                                    if(i == 0 && snake.get_dir() == 2) { }
                                    else if (i == 1 && snake.get_dir() == 3) { }
                                    else if (i ==  2 && snake.get_dir() == 0) { }
                                    else if (i == 3 && snake.get_dir() == 1) { }
                                    else if (i == snake.get_dir()) { }
                                    else
                                    {
                                        //Inserta un pivote solo si en esa casilla no hay uno aún
                                        bool canSpawn = true;
                                        if(!pivot_list.empty())
                                        {
                                            for (int j = 0; j < pivot_list.size(); ++j) {
                                                if(snake.current_cell.contains(pivot_list[i].position))
                                                    canSpawn = false;
                                            }

                                        }

                                        if(canSpawn)
                                        {
                                            pivot_list.emplace_back(
                                                    Pivot({ snake.get_x(), snake.get_y() }, i, snake.current_cell)
                                            );
                                            snake.change_direction(i);
                                        }
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
                    touch_location =
                            {
                                    *event[ID(x)].as< var::Float > (),
                                    *event[ID(y)].as< var::Float > ()
                            };
                    //Si se levanta sobre el botón de pausa se para el juego
                    if(cells[0][0].contains(touch_location))
                        state = PAUSED;

                    if(touched_controller)
                    {
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
            case PAUSED: break;
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

                //Se pinta en la celda de los pivotes un fragmento de serpiente que representa el giro
                for (int i = 0; i < pivot_list.size(); ++i) {
                    canvas->set_color(0.26f, 0.6f, 0.97f);
                    canvas->fill_rectangle(pivot_list[i].pivot_cell.position, {Cell::size, Cell::size});
                }

                for (int i = 0; i < controllers.size(); ++i) {
                    controllers[i]->render(*canvas);
                }

                //Se pinta el botón de pausa
                canvas->set_color(235/255.f, 180/255.f, 52/255.f);
                canvas->fill_rectangle( { cells[0][0].position[0] + 2, cells[0][0].position[1] + Cell::size / 5 },
                                        { Cell::size - 4, Cell::size / 5 });

                canvas->fill_rectangle( { cells[0][0].position[0] + 2, cells[0][0].position[1] + (Cell::size / 5) * 3 },
                                        { Cell::size - 4, Cell::size / 5 });
            }
        }
        else if(!suspended && state == PAUSED)
        {
            //Se pinta la textura que hace de menu de pausa
            if (pause_texture)
            {
                Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

                canvas->fill_rectangle
                        (
                                { canvas_width * .5f, canvas_height * .5f },
                                { pause_texture->get_width (), pause_texture->get_height () },
                                pause_texture. get ()
                        );
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

                    food = Food(cells[Cell::board_width/2][(Cell::board_height/3) * 2 + 1]);

                    pause_texture = Texture_2D::create (0, context, "pause.png");

                    // Se comprueba si la textura se ha podido cargar correctamente:

                    context->add (pause_texture);



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

        if(snake.check_endgame_collision())
            restart_game();


    }

    void Sample_Scene::create_cells()
    {
        //Cells start points
        float offset_x = 0, offset_y = start_point;
        for (int i = 0; i < Cell::board_width; ++i)
        {
            //Each row (vertical)
            for (int j = 0; j < Cell::board_height; ++j)
            {
                //Each column (vertical)
                if((j == 0 || j == Cell::board_height - 1) || (i == 0 || i == Cell::board_width - 1))
                {
                    //Creamos los bordes
                    cells[i][j] = Cell(offset_x, offset_y, BORDER);
                }
                else
                {
                    //El resto de casillas estarán libres
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

                if(cells[i][j].status == BORDER)
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
                canvas.fill_rectangle( cells[i][j].position , {cells[i][j].size, cells[i][j].size});




            }

        }

    }

    void Sample_Scene::calculate_start_point()
    {
        //Se calcula donde debe empezar y acabar el tablero para que siempre esté
        //en el medio de la pantalla
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

    void Sample_Scene::restart_game()
    {
        snake.sb.clear();
        pivot_list.clear();

        for (int i = 0; i < Cell::board_width; ++i)
        {
            for (int j = 0; j < Cell::board_height; ++j)
            {
                if((j == 0 || j == Cell::board_height - 1) || (i == 0 || i == Cell::board_width - 1))
                {
                    cells[i][j].status = BORDER;
                }
                else
                {
                    cells[i][j].status = FREE;
                }
            }
        }

        first_touch = true;

        snake = Snake(cells[Cell::board_width/2][Cell::board_height/3]);
        snake.sb.emplace_back(
                snake_body(cells[Cell::board_width/2][Cell::board_height/3 - 1])
        );
        snake.calculate_current_cell(cells);
        food = Food(cells[Cell::board_width/2][(Cell::board_height/3) * 2 + 1]);
    }

}
