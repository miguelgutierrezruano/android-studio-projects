/*
 * MAIN
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */

#include <basics/Director>
#include <basics/enable>
#include <basics/Graphics_Resource_Cache>
#include <basics/Texture_2D>
#include <basics/Window>
#include <basics/opengles/Context>
#include <basics/opengles/Canvas_ES2>
#include <basics/opengles/OpenGL_ES2>
#include "Intro_Scene.h"

using namespace basics;
using namespace snake;
using namespace std;

int main ()
{
    // Es necesario habilitar un backend gráfico antes de nada:

    enable< basics::OpenGL_ES2 > ();

    // Se crea una escena y se inicia mediante el Director:

    director.run_scene (shared_ptr< Scene >(new Intro_Scene));

    return 0;
}
