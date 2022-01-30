/*
 * HELPER
 * Copyright © 2022+ Miguel Gutiérrez Ruano
 *
 * miguelgutierrezruano@gmail.com
 */
#pragma once

using namespace basics;
namespace snake
{
    struct helper
    {
        //Pense que necesitaría mas funciones globales, deje la de la distancia aquí
        //a android studio no le gusta que borre clases
        static float distance(Vector2f p1, Vector2f p2)
        {
            float dist;

            dist = sqrt(((p2[0] - p1[0]) * (p2[0] - p1[0])) + ((p2[1] - p1[1]) * (p2[1] - p1[1])));

            return dist;
        }
    };

}


