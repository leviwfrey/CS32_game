#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cmath>

class Controller {
    public:

        void update() {

            // detect SINGLE key down
            if(keyStates['d'] && !keyStates['a']) {
                fix_x_dir = 1;
            } else if(keyStates['a'] && !keyStates['d']) {
                fix_x_dir = -1;
            }

            if(keyStates['w'] && !keyStates['s']) {
                fix_y_dir = 1;
            } else if(keyStates['s'] && !keyStates['w']) {
                fix_y_dir = -1;
            }

            // detect MULTIPLE key down
            if(fix_x_dir > 0) {
                if(keyStates['a']) {
                    x_dir = -1;
                } else {
                    x_dir = 1;
                }
            } else if(fix_x_dir < 0) {
                if(keyStates['d']) {
                    x_dir = 1;
                } else {
                    x_dir = -1;
                }
            }

            if(fix_y_dir > 0) {
                if(keyStates['s']) {
                    y_dir = -1;
                } else {
                    y_dir = 1;
                }
            } else if(fix_y_dir < 0) {
                if(keyStates['w']) {
                    y_dir = 1;
                } else {
                    y_dir = -1;
                }
            }

            // dectect NO key down
            if(!keyStates['d'] && !keyStates['a']) {
                x_dir = 0;
                fix_x_dir = 0;
            }
            if(!keyStates['w'] && !keyStates['s']) {
                y_dir = 0;
                fix_y_dir = 0;
            }
           
           //adjust for diagonal movement
           if(x_dir != 0 && y_dir != 0) {
                x_dir *= .707;
                y_dir *= .707;
           } else {
                if(x_dir != 0) {
                    x_dir = x_dir * (1/fabs(x_dir));
                }
                if(y_dir != 0) {
                    y_dir = y_dir * (1/fabs(y_dir));
                }
           }
        }
    
        double getYdir() {
            return y_dir;
        }

        double getXdir() {
            return x_dir;
        }

        void setKey(unsigned char key, bool pressed) {
            keyStates[key] = pressed;
        }

        void setMousePos(Vector2d pos) {
            mousePos = pos;
        }

        Vector2d getMousePos() const {
            return mousePos;
        }

    private:
        bool keyStates[256];
        double fix_x_dir = 0;
        double fix_y_dir = 0;
        double x_dir = 0;
        double y_dir = 0;

        Vector2d mousePos = Vector2d(0, 0);
};

#endif