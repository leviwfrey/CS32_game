#ifndef ENTITY_H
#define ENTITY_H
#include "Vector2d.h"
#include "Controller.h"
#include <vector>
#include <string>
#include <memory>
#include "Collider.h"
#include "TimerHandler.h"
#include <chrono>

using namespace std;

class EntityHandler;

class HealthBar {
    public:
    HealthBar(double width, int maxHP);
    void damage(int amount);
    void draw(Vector2d position) const;
    int current() const;
    int max() const;
    bool empty() const;

    private:
        double width;
        int maxHP;
        int currentHP;
};

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
        bool alive(){return isAlive;}
        bool isEnemy(){return _isEnemy;}

    protected:
        Vector2d pos = Vector2d(0, 0);
        Vector2d vel = Vector2d(0, 0);
        double rot = 0;
        Collider collider = Collider(0);
        string group = "all";
        bool isAlive = true;
        bool _isEnemy;
};

class Player: public Entity {
    using PlayerTimerHandler = TimerHandler<Player>;
    public:
        Player(shared_ptr<EntityHandler> entityHandler, Vector2d position = Vector2d(0, 0), double size = 50);

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);
        void resetCoolDown();

        Controller controller;   

        

    private:

        //model
        vector<Vector2d> body;
        vector<Vector2d> muzzle; 
        Vector2d projSpawnPoint = Vector2d(0, 0);
        double size;

        //physics
        double speed = 11;

        //weapon
        chrono::milliseconds weaponCooldown = chrono::milliseconds(250);
        bool canShoot = true;
        PlayerTimerHandler timers;
        shared_ptr<EntityHandler> entityHandler;
};

class Npc: public Entity {

    public:
        Npc(Vector2d position = Vector2d(0, 0), double size = 50, shared_ptr<Player> _player = nullptr);

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

        double size = 40;
        

        vector<Vector2d> body;

        
    private:
        double speed = 3;
        shared_ptr<Player> player;
        HealthBar healthBar = HealthBar(55, 100); //width, maxHp
        Vector2d healthBarPos;

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