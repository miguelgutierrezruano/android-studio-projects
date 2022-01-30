/*
 * SAMPLE_SCENE
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#include "cell.h"
#include "snake.h"
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
        bool     aspect_ratio_adjusted;

        float start_point;
        float last_point;
        Vector2f midpoint;


    public:

        enum State
        {
            LOADING,
            RUNNING,
            PAUSED
        };

        State          state;
        bool           suspended;

        unsigned       canvas_width;
        unsigned       canvas_height;

        /**
         * Estructura Controller, triángulos que definen las flechas de dirección de
         * la serpiente
         */
        struct Controller
        {
            Vector2f points[3];
            Vector3f color;

            Controller() { };
            /**
            * Contructor determinado por 3 puntos y un color
            */
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

            /**
            * Método que comprueba si el punto dado está dentro del triágunlo
            * (en el mismo lado de las tres rectas que lo definen)
            */
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

            /**
            * Método que pinta los Controllers en el canvas
            */
            void render (basics::Canvas & canvas)
            {
                canvas.set_color( color[0], color[1], color[2] );
                canvas.fill_triangle( { points[0] },
                                      { points[1] },
                                      { points[2] } );
            }

        };

        ///Tablero de celdas
        Cell cells[Cell::board_width][Cell::board_height];
        ///Vector de pivotes
        vector<Pivot> pivot_list;

        Snake snake;
        Food food;


        //Handle
        bool first_touch;
        Vector2f touch_location;
        vector< shared_ptr< Controller > > controllers;
        Controller * touched_controller;

        std::shared_ptr < Texture_2D > pause_texture;

    public:

        Sample_Scene();

        basics::Size2u get_view_size () override
        {
            return { canvas_width, canvas_height };
        }

        bool initialize () override;
        void suspend    () override;
        void resume     () override;

        /**
        * Se encarga de comprobar cuando se toca la pantalla y controla el juego
        */
        void handle     (basics::Event & event) override;

        void update     (float time) override;

        /**
        * Pinta la escena en el canvas creado del context
        */
        void render     (basics::Graphics_Context::Accessor & context) override;

    private:
        /**
        * Carga la escena inicial, ajustando el juego a la pantalla e inicializando
        * todos los objetos
        */
        void load ();
        /**
        * Update del juego, principalmente la serpiente
        */
        void run  (float time);

        /**
        * Método para crear las celdas
        */
        void create_cells();
        /**
        * Método para dibujar las celdas en el canvas dado
        */
        void draw_cells(basics::Canvas & canvas);
        /**
        * Método para crear los controles en sus posiciones
        */
        void create_controllers();

        /**
        * Calcula las posiciones clave para pintar los objetos
        * correctamente, independientemente del tamaño de la pantalla
        */
        void calculate_start_point();

        /**
        * Método para reiniciar la partida
        */
        void restart_game();

    };

}
