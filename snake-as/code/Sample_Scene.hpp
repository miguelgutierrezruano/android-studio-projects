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
#include <memory>
#include <basics/Scene>
#include <basics/Canvas>
#include <basics/Texture_2D>
#include <vector>

namespace snake
{

    class Sample_Scene : public basics::Scene
    {

    private:
        bool     aspect_ratio_adjusted;             ///< false hasta que se ajuste el aspect ratio de la resolución
        ///< virtual para que concincida con el de la real


    public:

        static constexpr unsigned board_width = 14;
        static constexpr unsigned board_height = 17;

        enum State
        {
            LOADING,
            RUNNING,
        };

        State          state;
        bool           suspended;

        unsigned       canvas_width;
        unsigned       canvas_height;


        Snake snake;
        Cell cells[board_width][board_height];
        //std::vector<std::vector<Cell>> v_cells;

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
        void create_cells();
        void draw_cells(basics::Canvas*);

    };

}
