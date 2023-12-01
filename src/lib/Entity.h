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
            drawPoly(pos, body, rot, .392, .541, .169);
            drawPoly(pos, muzzle, rot);
        }

        void update() {
            rot = pos.angleTo(controller.getMousePos());
            controller.update();
            vel.x = max_vel*controller.getXdir();
            vel.y = max_vel*controller.getYdir();
            pos.x += vel.x;
            pos.y += vel.y;
        }

        Controller controller;   
        double max_vel = 10;

        double size = 100;

        Vector2d p1 = Vector2d(-size/2, size/2);
        Vector2d p2 = Vector2d(size/2, size/2);

        Vector2d p3 = Vector2d(size/2, size/5);
        Vector2d p4 = Vector2d(size/2+size*.4, size/5);
        Vector2d p5 = Vector2d(size/2+size*.4, -size/5);
        Vector2d p6 = Vector2d(size/2, -size/5);

        Vector2d p7 = Vector2d(size/2, -size/2);
        Vector2d p8 = Vector2d(-size/2, -size/2);

        vector<Vector2d> body = {p1,p2,p7,p8};
        vector<Vector2d> muzzle = {p3, p4, p5, p6};

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