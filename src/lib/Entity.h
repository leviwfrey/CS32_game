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
        Player(shared_ptr<EntityHandler> entityHandler, Vector2d position = Vector2d(0, 0), double size = 50);

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

        Controller controller;   

        

    private:
        vector<Vector2d> body;
        vector<Vector2d> muzzle; 
        Vector2d projSpawnPoint = Vector2d(0, 0);
        double size;
        double speed = 8;
        shared_ptr<EntityHandler> entityHandler;
};

class Npc: public Entity {

    public:
        Npc(Vector2d position = Vector2d(0, 0), double size = 50);

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

        double size = 40;
        Vector2d p1 = Vector2d(-size/2, size/2);
        Vector2d p2 = Vector2d(size/2, size/2);
        Vector2d p3 = Vector2d(size/2, -size/2);
        Vector2d p4 = Vector2d(-size/2, -size/2);

        vector<Vector2d> body = {p1,p2,p3,p4};
};

class Projectile : public Entity {
    public:
        Projectile(Vector2d position, double rot, double size = 26, string group = "Projectiles");

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

    private:
        vector<Vector2d> model;
        double size;
        double speed = 20;



};

#endif