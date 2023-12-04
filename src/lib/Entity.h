#ifndef ENTITY_H
#define ENTITY_H
#include "Vector2d.h"
#include "Controller.h"
#include <vector>
#include <string>
#include <memory>
#include "Collider.h"

using namespace std;

class EntityHandler;

class Entity { 

    public:

        Entity();
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void handleCollision(shared_ptr<Entity> collision) = 0;

        string getGroup() const;

        Vector2d getPosition() const;
        void setPosition(Vector2d position);

        Vector2d getVelocity() const;
        void setVelocity(Vector2d velocity);

        double getRotation() const;
        void setRotation(double rotation); 

        Collider getCollider() const;

    protected:
        Vector2d pos = Vector2d(0, 0);
        Vector2d vel = Vector2d(0, 0);
        double rot = 0;
        Collider collider = Collider(0);
        string group = "all";
};

class Player: public Entity {

    public:
        Player(shared_ptr<EntityHandler> entityHandler, Vector2d position = Vector2d(0, 0));

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

        Controller controller;   

        double size = 50;

        // Model for player
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

    private:
        double speed = 10;
        shared_ptr<EntityHandler> entityHandler;
};

class Npc: public Entity {

    public:
        Npc(Vector2d position = Vector2d(0, 0), double size = 50);

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

        double size;
        Vector2d p1 = Vector2d(-size/2, size/2);
        Vector2d p2 = Vector2d(size/2, size/2);
        Vector2d p3 = Vector2d(size/2, -size/2);
        Vector2d p4 = Vector2d(-size/2, -size/2);

        vector<Vector2d> body = {p1,p2,p3,p4};


    private:
};

#endif