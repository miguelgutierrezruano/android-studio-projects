/*
 * SAMPLE SCENE
 * Copyright © 2018+ Miguel Gutierrez
 */

#include "Square.h"
#include <memory>
#include <basics/Canvas>
#include <basics/Scene>
#include <vector>
#include <random>
#include <math.h>
#include <array>

namespace example
{

    class Sample_Scene : public basics::Scene
    {
    private:

        bool     suspended;                         ///< true cuando la aplicación está en segundo plano
        unsigned canvas_width;                      ///< Resolución virtual del display
        unsigned canvas_height;

        //std::vector<Square> square[2];
        Square square2;
        Square square1;

        float delay;

        std::array<float, 3> colorArray;



    public:

        Sample_Scene()
        {
            canvas_width  = 1280;                   // Todavía no se puede calcular el aspect ratio, por lo que se establece
            canvas_height =  720;                   // un tamaño por defecto hasta poder calcular el tamaño final

        }

        basics::Size2u get_view_size () override
        {
            return { canvas_width, canvas_height };
        }

        bool initialize () override
        {

            for (int i = 0; i < colorArray.size(); ++i) {
                colorArray[i] = 1;
            }

            square1.x = random(square1.get_size(), canvas_width - square1.get_half_size());
            square1.y = random(square1.get_size(), canvas_height - square1.get_half_size());

            square2.x = random(square1.get_size(), canvas_width - square1.get_half_size());
            square2.y = random(square1.get_size(), canvas_height - square1.get_half_size());

            delay = 0;

            suspended = false;

            return true;
        }

        float random (float min, float max)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<float> dist(min, max);

            return dist(mt);
        }

        float distance(float, float , float , float);

        void suspend () override;
        void resume () override;

        void update (float) override;
        void render (basics::Graphics_Context::Accessor & context) override;

    };

}
