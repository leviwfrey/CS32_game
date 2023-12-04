#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <cmath>
#include <GL/glut.h>
#include <vector>

using namespace std;

class Vector2d {
    public:

        Vector2d(double x, double y) {
            this->x = x;
            this->y = y;
        }

        Vector2d() {}

        double x;
        double y; 
        
        Vector2d rotate(double& angle) const { // returns a new vector rotated by a specified angle
            Vector2d rVec;
            rVec.x = x*cos(angle) - y*sin(angle);
            rVec.y = x*sin(angle) + y*cos(angle);
            return rVec;
        }

        double getAngle() const {
            if(x == 0) {
                if(y >= 0) {
                    return M_PI/2;
                } else {
                    return -M_PI/2;
                }
            } else {
                double angle = atan(y/x);
                if(x < 0) {
                    if(y < 0) {
                        return -M_PI+angle;
                    } else if(y > 0) {
                        return M_PI+angle;
                    } else {
                        return M_PI;
                    }
                } else {
                    return angle;
                }
            }
        }

        Vector2d difference(Vector2d& other) const {
            return Vector2d(x - other.x, y - other.y);
        }

        Vector2d normalized() const {
            if(x == 0 && y == 0) {
                return Vector2d(0, 0);
            }
            return Vector2d(x/magnitude(), y/magnitude());
        }

        double magnitude() const {
            return sqrt(pow(x, 2) + pow(y, 2));
        }

        double distanceTo(Vector2d other) {
            return difference(other).magnitude();
        }

        static void drawPoly(Vector2d center, vector<Vector2d> points, double angle, double R=1.0, double G=1.0, double B=1.0, double A=1) {
            glColor4f(R,G,B,A);
            glBegin(GL_POLYGON);
            for(Vector2d p : points) {
                p = p.rotate(angle);
                glVertex3f(center.x + p.x, center.y + p.y, 0.0);
            }
            glEnd();
}

};



#endif