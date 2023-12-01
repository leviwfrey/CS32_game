#ifndef ENTITY_H
#define ENTITY_H
#include "Point.h"
#include "Draw.h"
#include "Controller.h"

class Entity { 
    public:
        virtual void draw() = 0;
        virtual void update() = 0;
    protected:
        Point pos;
        double size;

        double max_vel;
        double x_vel = 0; 
        double y_vel = 0; 
};

class Player: public Entity {

    public:
        Player(double x, double y) {
            pos.x = x;
            pos.y = y;
            size = .15;
            max_vel = .1;
        }

        void draw() override{
            drawSquare(size, pos);
        }

        void update() {
            controller.update();
            x_vel = max_vel*controller.getXdir();
            y_vel = max_vel*controller.getYdir();
            pos.x += x_vel;
            pos.y += y_vel;
        }

        Controller controller;       
};

class Npc: public Entity {

    public:
        Npc(double x, double y) {
            pos.x = x;
            pos.y = y;
            max_vel = .08;
            size = .05;
        }

        void draw() override{
            drawSquare(size, pos);
        }

        void update() {
            x_vel = max_vel;
            y_vel = max_vel;
            pos.x += x_vel;
            pos.y += y_vel;
        }
};

#endif