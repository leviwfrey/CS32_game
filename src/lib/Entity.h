#ifndef ENTITY_H
#define ENTITY_H
#include "Vector2d.h"
#include "Draw.h"
#include "Controller.h"
#include <vector>

using namespace std;


class Entity { 
    public:
        virtual void draw() = 0;
        virtual void update() = 0;
    protected:
        Vector2d pos;
        Vector2d vel;

        double max_vel;
        double rot = 0;
        
};

class Player: public Entity {

    public:
        Player(double x, double y) {
            pos = Vector2d(x, y);
        }

        void draw() override {
            drawPoly(pos, points, rot);
        }

        void update() {
            rot += .1;
            controller.update();
            vel.x = max_vel*controller.getXdir();
            vel.y = max_vel*controller.getYdir();
            pos.x += vel.x;
            pos.y += vel.y;
        }

        Controller controller;   
        double max_vel = .03;

        double size = .12;

        Vector2d p1 = Vector2d(-size/2, size/2);
        Vector2d p2 = Vector2d(size/2, size/2);
        Vector2d p3 = Vector2d(size/2, -size/2);
        Vector2d p4 = Vector2d(-size/2, -size/2);
        vector<Vector2d> points = {p1,p2,p3,p4};

};

class Npc: public Entity {

    public:
        Npc(double x, double y) {
            pos.x = x;
            pos.y = y;
            max_vel = .08;
        }

        void draw() override{
            drawSquare(size, pos);
        }

        void update() {
            vel.x = max_vel;
            vel.y = max_vel;
            pos.x += vel.x;
            pos.y += vel.y;
        }

    private:
        double size = .04;
};

#endif