#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>

class Vector2d {
    public:

        Vector2d(double x, double y) {
            this->x = x;
            this->y = y;
        }

        Vector2d() {}

        double x;
        double y;
        
        Vector2d rotate(double angle) {
            Vector2d rVec;
            rVec.x = x*cos(angle) - y*sin(angle);
            rVec.y = x*sin(angle) + y*cos(angle);
            return rVec;
        }
};



#endif