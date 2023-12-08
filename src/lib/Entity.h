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
#include <random>


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

class Weapon {
    using WeaponTimerHandler = TimerHandler<Weapon>;
    public:
        virtual void shoot(Vector2d& position, double& rot, shared_ptr<EntityHandler>& handler, string group) = 0;
        void resetCooldown() { ready = true; }
        void update() { timers.update(); }
        bool canShoot() const { return ready; }

    protected:
        bool ready = true;
        WeaponTimerHandler timers = WeaponTimerHandler();

};

class Shotgun : public Weapon {
    public:
        void shoot(Vector2d& position, double& rot, shared_ptr<EntityHandler>& handler, string group);

    private:
        double size = 13;
        Vector2d p1 = Vector2d(size/2, 0);
        Vector2d p2 = Vector2d(-size/2, -size/2*.8);
        Vector2d p3 = Vector2d(-size/2, size/2*.8);

        vector<Vector2d> model = {p1, p2, p3};
        double speed = 20;
        double damage = 2;
        chrono::milliseconds cooldown = chrono::milliseconds(250); //sets weapon cooldown
};

class Sniper : public Weapon {
    public:
        void shoot(Vector2d& position, double& rot, shared_ptr<EntityHandler>& handler, string group);
    private:
        double size = 20;
        Vector2d p1 = Vector2d(-size/2, size/3);
        Vector2d p2 = Vector2d(size/2, size/3);
        Vector2d p3 = Vector2d(size/2, -size/3);
        Vector2d p4 = Vector2d(-size/2, -size/3);
        vector<Vector2d> model = {p1,p2,p3,p4};
        double speed = 20;
        double damage = 75;
        chrono::milliseconds cooldown = chrono::milliseconds(1100);
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

        void kill();

        void damage(int amount);

    protected:
        Vector2d pos = Vector2d(0, 0);
        Vector2d vel = Vector2d(0, 0);
        double rot = 0;
        Collider collider = Collider(0);
        string group = "all";
        bool isAlive = true;
        HealthBar healthBar = HealthBar(100, 50);
        double size = 50;
};

class Player: public Entity {
    
    public:
        Player(shared_ptr<EntityHandler> entityHandler, Vector2d position = Vector2d(0, 0), double size = 50);

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

        Controller controller;   

        

    private:

        //model
        vector<Vector2d> body;
        vector<Vector2d> muzzle; 
        Vector2d projSpawnPoint = Vector2d(0, 0);
        double size;

        //physics
        double speed = 8;

        //weapon
        shared_ptr<Weapon> weapon = make_shared<Shotgun>();
        shared_ptr<EntityHandler> entityHandler;
};

class Npc: public Entity {

    public:
        Npc(Vector2d position, double size, shared_ptr<Player> _player, double speed);

        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);


        vector<Vector2d> body;

        
    private:
        double speed;
        double hp = 50; //sets the hp
        shared_ptr<Player> player;
        Vector2d healthBarPos;

};

class SniperEnemy : public Entity {
    public:
        SniperEnemy(Vector2d position, double size, shared_ptr<Player> player, shared_ptr<EntityHandler> entityHandler);

    void draw();
    void update();
    void handleCollision(shared_ptr<Entity> entity);
    
        
    private:
        shared_ptr<Weapon> weapon = make_shared<Sniper>();
        shared_ptr<EntityHandler> entityHandler;
        
        shared_ptr<Player> player;

        Vector2d firePoint;
        Vector2d healthBarPos;
        vector<Vector2d> model;

        double range = 750;
        double speed = 3;
        double hp = 50;
};

class Projectile : public Entity {
    public:
        Projectile(vector<Vector2d>& model, Vector2d& position, double rotation, double size, double speed, double damage, string group, double R = 1.0, double G = 1.0, double B = 1.0);
        void draw();
        void update();
        void handleCollision(shared_ptr<Entity> entity);

    private:
        vector<Vector2d> model;
        double size;
        double speed;
        double damage;
        double R;
        double G;
        double B;

};



#endif