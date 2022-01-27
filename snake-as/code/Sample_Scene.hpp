/*
 * SAMPLE SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "cell.h"
#include "snake.h"
#include "Food.h"
#include <memory>
#include <basics/Scene>
#include <basics/Canvas>
#include <basics/Texture_2D>
#include <vector>
#include <list>

namespace snake
{

    class Sample_Scene : public basics::Scene
    {

    private:
        bool     aspect_ratio_adjusted;             ///< false hasta que se ajuste el aspect ratio de la resolución
        ///< virtual para que concincida con el de la real

        float start_point;
        float last_point;
        Vector2f midpoint;


    public:

        //static constexpr unsigned board_width = 17;
        //static constexpr unsigned board_height = 14;

        enum State
        {
            LOADING,
            RUNNING,
        };

        State          state;
        bool           suspended;

        unsigned       canvas_width;
        unsigned       canvas_height;



        //std::vector<std::vector<Cell>> v_cells;

        struct Controller
        {
            Vector2f points[3];
            Vector3f color;

            Controller() { };
            Controller(const Vector2f p1, const Vector2f p2, const Vector2f p3, const Vector3f _color)
            {
                points[0] = p1;
                points[1] = p2;
                points[2] = p3;
                color = _color;
            }

            float sign (Vector2f p1, Vector2f p2, Vector2f p3) const
            {
                return (p1.coordinates.x() - p3.coordinates.x()) * (p2.coordinates.y() - p3.coordinates.y()) -
                        (p2.coordinates.x() - p3.coordinates.x()) * (p1.coordinates.y() - p3.coordinates.y());
            }

            bool contains (const Vector2f point) const
            {
                float d1, d2, d3;
                bool has_neg, has_pos;

                d1 = sign(point, points[0], points[1]);
                d2 = sign(point, points[1], points[2]);
                d3 = sign(point, points[2], points[0]);

                has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
                has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

                return !(has_neg && has_pos);
            }

            void render (basics::Canvas & canvas)
            {
                canvas.set_color( color[0], color[1], color[2] );
                canvas.fill_triangle( { points[0] },
                                      { points[1] },
                                      { points[2] } );
            }

        };

        Cell cells[Cell::board_width][Cell::board_height];
        vector<Pivot> pivot_list;

        Snake snake;
        Food food;


        //Handle
        bool first_touch;
        Vector2f touch_location;
        vector< shared_ptr< Controller > > controllers;
        Controller * touched_controller;

    public:

        Sample_Scene();

        basics::Size2u get_view_size () override
        {
            return { canvas_width, canvas_height };
        }

        bool initialize () override;
        void suspend    () override;
        void resume     () override;

        void handle     (basics::Event & event) override;
        void update     (float time) override;
        void render     (basics::Graphics_Context::Accessor & context) override;

    private:

        void load ();
        void run  (float time);

        //REFACTOR TO CLASS
        void create_cells();
        void draw_cells(basics::Canvas & canvas);
        void create_controllers();
        void calculate_start_point();

    };

}
