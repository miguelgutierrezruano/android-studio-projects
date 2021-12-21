/*
 * MAIN
 * Copyright © 2021 Miguel Gutiérrez
 */

#include <basics/Director>
#include <basics/enable>
#include <basics/Graphics_Resource_Cache>
#include <basics/Texture_2D>
#include <basics/Window>
#include <basics/opengles/Context>
#include <basics/opengles/Canvas_ES2>
#include <basics/opengles/OpenGL_ES2>

#include "Sample_Scene.hpp"

using namespace basics;
using namespace example;
using namespace std;

int main ()
{
    // Es necesario habilitar un backend gráfico antes de nada:

    enable< basics::OpenGL_ES2 > ();

    // Se crea una escena y se inicia mediante el Director:

    director.run_scene (shared_ptr< Scene >(new Sample_Scene));

    return 0;
}

// El linker tiende a eliminar código que cree que no se usa y, cuando se termina usando, lo echa en
// falta provocando errores. Dejar estas referencias aquí por el momento para evitar esos problemas:

void keep_links ()
{
    (void)Window::can_be_instantiated;
    Window::Accessor window;
    Window::create_window (0);
    Window::get_window (0);
    Graphics_Resource_Cache cache;
    opengles::Context::create(window, &cache);
    Canvas::Factory f = opengles::Canvas_ES2::create;
    Texture_2D::register_factory (0, 0);
}
