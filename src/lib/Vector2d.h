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
        
        Vector2d rotate(double angle) { // returns a new vector rotated by a specified angle
            Vector2d rVec;
            rVec.x = x*cos(angle) - y*sin(angle);
            rVec.y = x*sin(angle) + y*cos(angle);
            return rVec;
        }

        double angleTo(Vector2d fixed) { // finds angle to two points, assuming the angle being called from is at 0 radians;
            double dx = fixed.x - x;
            double dy = fixed.y - y;
            if(dx == 0) {
                if(dy >= 0) {
                    return M_PI/2;
                } else {
                    return -M_PI/2;
                }
            } else {
                double angle = atan(dy/dx);
                if(dx < 0) {
                    if(dy < 0) {
                        return -M_PI+angle;
                    } else if(dy > 0) {
                        return M_PI+angle;
                    } else {
                        return M_PI;
                    }
                } else {
                    return angle;
                }
            }
        }
};



#endif