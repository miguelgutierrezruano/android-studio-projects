/*
 * MENU SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#ifndef MENU_SCENE_HEADER
#define MENU_SCENE_HEADER

#include <memory>
#include <basics/Atlas>
#include <basics/Canvas>
#include <basics/Point>
#include <basics/Scene>
#include <basics/Size>
#include <basics/Timer>
#include <basics/Director>
#include <basics/Transformation>
#include "Sample_Scene.hpp"

namespace snake
{

    using basics::Atlas;
    using basics::Timer;
    using basics::Canvas;
    using basics::Point2f;
    using basics::Size2f;
    using basics::Texture_2D;
    using basics::Graphics_Context;

    class Menu_Scene : public basics::Scene
    {

        /**
         * Representa el estado de la escena en su conjunto.
         */
        enum State
        {
            LOADING,
            READY,
            FINISHED,
            ERROR
        };

        enum Option_Id
        {
            PLAY,
            SCORES,
            HELP,
            CREDITS
        };

        struct Option
        {
            const Atlas::Slice * slice;
            Point2f position;
            float   is_pressed;
        };

        static const unsigned number_of_options = 4;

    private:

        State    state;                                     ///< Estado de la escena.
        bool     suspended;                                 ///< true cuando la escena está en segundo plano y viceversa.

        unsigned canvas_width;                              ///< Ancho de la resolución virtual usada para dibujar.
        unsigned canvas_height;                             ///< Alto  de la resolución virtual usada para dibujar.
        bool aspect_ratio_adjusted;

        Timer    timer;                                     ///< Cronómetro usado para medir intervalos de tiempo.

        Option   options[number_of_options];                ///< Datos de las opciones del menú

        std::unique_ptr< Atlas > atlas;                     ///< Atlas que contiene las imágenes de las opciones del menú

    public:

        Menu_Scene()
        {
            state         = LOADING;
            suspended     = true;
            canvas_width  = 1280;
            canvas_height =  720;
            aspect_ratio_adjusted = false;
        }

        /**
         * Este método lo llama Director para conocer la resolución virtual con la que está
         * trabajando la escena.
         * @return Tamaño en coordenadas virtuales que está usando la escena.
         */
        basics::Size2u get_view_size () override
        {
            return { canvas_width, canvas_height };
        }

        /**
         * Aquí se inicializan los atributos que deben restablecerse cada vez que se inicia la escena.
         * @return
         */
        bool initialize () override
        {
            for (auto & option : options)
            {
                option.is_pressed = false;
            }

            return true;
        }

        /**
         * Este método lo invoca Director automáticamente cuando el juego pasa a segundo plano.
         */
        void suspend () override
        {
            suspended = true;
        }

        /**
         * Este método lo invoca Director automáticamente cuando el juego pasa a primer plano.
         */
        void resume () override
        {
            suspended = false;
        }

        /**
         * Este método se invoca automáticamente una vez por fotograma cuando se acumulan
         * eventos dirigidos a la escena.
         */
        void handle (basics::Event & event) override
        {
            if (state == READY)                     // Se descartan los eventos cuando la escena está LOADING
            {
                switch (event.id)
                {
                    case ID(touch-started):         // El usuario toca la pantalla
                    case ID(touch-moved):
                    {
                        // Se determina qué opción se ha tocado:

                        Point2f touch_location = { *event[ID(x)].as< var::Float > (), *event[ID(y)].as< var::Float > () };
                        int     option_touched = option_at (touch_location);

                        // Solo se puede tocar una opción a la vez (para evitar selecciones múltiples),
                        // por lo que solo una se considera presionada (el resto se "sueltan"):

                        for (int index = 0; index < number_of_options; ++index)
                        {
                            options[index].is_pressed = index == option_touched;
                        }

                        break;
                    }

                    case ID(touch-ended):           // El usuario deja de tocar la pantalla
                    {
                        // Se "sueltan" todas las opciones:

                        for (auto & option : options) option.is_pressed = false;

                        // Se determina qué opción se ha dejado de tocar la última y se actúa como corresponda:

                        Point2f touch_location = { *event[ID(x)].as< var::Float > (), *event[ID(y)].as< var::Float > () };

                        if (option_at (touch_location) == PLAY)
                        {
                            basics::director.run_scene (shared_ptr< Scene >(new Sample_Scene));
                        }

                        break;
                    }
                }
            }
        }

        /**
         * Este método se invoca automáticamente una vez por fotograma para que la escena
         * actualize su estado.
         */
        void update (float time) override
        {
            if (!suspended) if (state == LOADING)
                {
                    Graphics_Context::Accessor context = basics::director.lock_graphics_context ();

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
                        }

                        // Se carga el atlas:

                        atlas.reset (new Atlas("menu_text.sprites", context));

                        // Si el atlas se ha podido cargar el estado es READY y, en otro caso, es ERROR:

                        state = atlas->good () ? READY : ERROR;

                        // Si el atlas está disponible, se inicializan los datos de las opciones del menú:

                        if (state == READY)
                        {
                            configure_options ();
                        }
                    }
                }
        }

        /**
         * Este método se invoca automáticamente una vez por fotograma para que la escena
         * dibuje su contenido.
         */
        void render (Graphics_Context::Accessor & context) override
        {
            if (!suspended)
            {
                // El canvas se puede haber creado previamente, en cuyo caso solo hay que pedirlo:

                Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

                // Si no se ha creado previamente, hay que crearlo una vez:

                if (!canvas)
                {
                    canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
                }

                // Si el canvas se ha podido obtener o crear, se puede dibujar con él:

                if (canvas)
                {
                    canvas->clear ();

                    if (state == READY)
                    {
                        // Se dibuja el slice de cada una de las opciones del menú:

                        for (auto & option : options)
                        {
                            canvas->set_transform
                                    (
                                            basics::scale_then_translate_2d
                                                    (
                                                            option.is_pressed ? 0.75f : 1.f,              // Escala de la opción
                                                            { option.position[0], option.position[1] }      // Traslación
                                                    )
                                    );

                            canvas->fill_rectangle ({ 0.f, 0.f }, { option.slice->width, option.slice->height }, option.slice, basics::CENTER | basics::TOP);
                        }

                        // Se restablece la transformación aplicada a las opciones para que no afecte a
                        // dibujos posteriores realizados con el mismo canvas:

                        canvas->set_transform (basics::Transformation2f());
                    }
                }
            }
        }

    private:

        /**
         * Establece las propiedades de cada opción si se ha podido cargar el atlas.
         */
        void configure_options ()
        {
            // Se asigna un slice del atlas a cada opción del menú según su ID:

            options[PLAY   ].slice = atlas->get_slice (ID(4)   );
            options[SCORES ].slice = atlas->get_slice (ID(5) );
            options[HELP   ].slice = atlas->get_slice (ID(6)   );
            options[CREDITS].slice = atlas->get_slice (ID(7));

            // Se calcula la altura total del menú:

            float menu_height = 0;

            for (auto & option : options) menu_height += option.slice->width;

            // Se calcula la posición del borde superior del menú en su conjunto de modo que
            // quede centrado verticalmente:

            float option_top = canvas_width / 2.f+ menu_height / 2.f;

            // Se establece la posición del borde superior de cada opción:

            for (unsigned index = 0; index < number_of_options; ++index)
            {
                options[index].position = Point2f{ option_top, canvas_height / 2.f };

                option_top -= options[index].slice->width + 50;
            }

            // Se restablece la presión de cada opción:

            initialize ();
        }

        /**
         * Devuelve el índice de la opción que se encuentra bajo el punto indicado.
         * @param point Punto que se usará para determinar qué opción tiene debajo.
         * @return Índice de la opción que está debajo del punto o -1 si no hay alguna.
         */
        int option_at (const Point2f & point)
        {
            for (int index = 0; index < number_of_options; ++index)
            {
                const Option & option = options[index];

                if
                        (
                        point[0] > option.position[0] - option.slice->width  &&
                        point[0] < option.position[0] + option.slice->width  &&
                        point[1] > option.position[1] - option.slice->height &&
                        point[1] < option.position[1] + option.slice->height
                        )
                {
                    return index;
                }
            }

            return -1;
        }

    };

}

#endif
