#ifndef ENTITY_H
#define ENTITY_H
#include "Point.h"
#include "Draw.h"

class Entity { 
    public:
        virtual void draw() = 0;
};

class Player: public Entity {

    public:
        Player(double _size, double _max_vel): max_vel(_max_vel) {
            p = {0,0}; //sets the initial point
            size = _size;
        }
        void draw() override{
            drawSquare(size, p);
        }
        void update(double controllerX, double controllerY) {
            x_vel = max_vel*controllerX;
            y_vel = max_vel*controllerY;
            p.x += x_vel;
            p.y += y_vel;
        }

        Point p;
        double size;
        const double max_vel;
        double x_vel = 0; 
        double y_vel = 0;    
};

class Npc: public Entity {

    public:
        Npc(double _size, double _max_vel, double initialX, double initialY): max_vel(_max_vel) {
            p = {initialX, initialY}; //sets the initial point
            size = _size;
        }
        void draw() override{
            drawSquare(size, p);
        }
        void update(double deltaX, double deltaY) {
            x_vel = max_vel*deltaX;
            y_vel = max_vel*deltaY;
            p.x += x_vel;
            p.y += y_vel;
        }

        Point p;
        double size;
        const double max_vel;
        double x_vel = 0;
        double y_vel = 0;
};

#endif