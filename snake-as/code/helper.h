//
// Created by migue on 25/01/2022.
//

using namespace basics;
namespace snake
{
    struct helper
    {
        static float distance(Vector2f p1, Vector2f p2)
        {
            float dist;

            dist = sqrt(((p2[0] - p1[0]) * (p2[0] - p1[0])) + ((p2[1] - p1[1]) * (p2[1] - p1[1])));

            return dist;
        }
    };

}


