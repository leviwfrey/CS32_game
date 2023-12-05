#include "Entity.h"
#include "EntityHandler.h"
#include <iostream>
#include <cmath>


// ENTITY

Entity::Entity() {}

string Entity::getGroup() const { return group; }

Vector2d Entity::getPosition() const { return pos; }
void Entity::setPosition(Vector2d position) { pos = position;}

Vector2d Entity::getVelocity() const { return vel; }
void Entity::setVelocity(Vector2d velocity) {vel = velocity;}

double Entity::getRotation() const { return rot; }
void Entity::setRotation(double rotation) {rot = rotation;}

Collider Entity::getCollider() const { return collider; }


// PLAYER
Player::Player(shared_ptr<EntityHandler> entityHandler, Vector2d position, double size) {
    this->pos = position;
    this->vel = Vector2d(0, 0);
    this->rot = controller.getMousePos().difference(pos).getAngle();
    this->group = "Players";
    this->collider = Collider(50, pos);
    this->entityHandler = entityHandler;

    this->size = size;
    // Model for player
    Vector2d p1 = Vector2d(-size/2, size/2);
    Vector2d p2 = Vector2d(size/2, size/2);

    Vector2d p3 = Vector2d(size/2, size/5);
    Vector2d p4 = Vector2d(size/2+size*.4, size/5);
    Vector2d p5 = Vector2d(size/2+size*.4, -size/5);
    Vector2d p6 = Vector2d(size/2, -size/5);

    Vector2d p7 = Vector2d(size/2, -size/2);
    Vector2d p8 = Vector2d(-size/2, -size/2);

    body = {p1,p2,p7,p8};
    muzzle = {p3, p4, p5, p6};

    projSpawnPoint = Vector2d(size, 0);
    
}

void Player::draw() {
    Vector2d::drawPoly(pos, body, rot, .392, .541, .169);
    Vector2d::drawPoly(pos, muzzle, rot, .7, .7, .7);
}

void Player::update() {
    rot = controller.getMousePos().difference(pos).getAngle();
    controller.update();
    vel.x = speed*controller.getXdir();
    vel.y = speed*controller.getYdir();
    pos.x += vel.x;
    pos.y += vel.y;
    collider.setPosition(pos);
    if(controller.spaceTriggered()) {
        Vector2d rotatedPos = projSpawnPoint.rotate(rot);
        Vector2d newPos = pos.add(rotatedPos);
        shared_ptr<Projectile> projectile = make_shared<Projectile>(newPos, rot);    
        entityHandler->addEntity(projectile, "Projectiles");
        projectile = make_shared<Projectile>(newPos, rot-(M_PI/10));
        entityHandler->addEntity(projectile, "Projectiles");
        projectile = make_shared<Projectile>(newPos, rot+(M_PI/10));
        entityHandler->addEntity(projectile, "Projectiles");
    }
}

void Player::handleCollision(shared_ptr<Entity> entity) {
    cout << getGroup() << " collided with " << entity->getGroup() << endl;
}

// NPC

Npc::Npc(Vector2d position, double size) {
    this->pos = position;
    this->size = size;
    this->collider = Collider(40);
    this->rot = 0;
    this->group = "Enemies";
}

void Npc::draw() {
    Vector2d::drawPoly(pos, body, rot, .1, .2, .3);
}

void Npc::update() {
}

void Npc::handleCollision(shared_ptr<Entity> entity) {
    cout << getGroup() << " collided with " << entity->getGroup() << endl;
}

// Projectile

Projectile::Projectile(Vector2d position, double rot, double size, string group) {
    this->pos = position;
    this->rot = rot;
    this->collider = Collider(size/2, pos);
    this->group = group;
    vel = Vector2d(speed, 0).rotate(rot);

    Vector2d p1 = Vector2d(size/2, 0);
    Vector2d p2 = Vector2d(-size/2, -size/2*.8);
    Vector2d p3 = Vector2d(-size/2, size/2*.8);

    model = {p1, p2, p3};
}

void Projectile::draw() {
    Vector2d::drawPoly(pos, model, rot, 1, 0, 0);
}

void Projectile::update() { 
    pos.x += vel.x;
    pos.y += vel.y;
    collider.setPosition(pos);
}

void Projectile::handleCollision(shared_ptr<Entity> entity) {
    cout << getGroup() << " collided with " << entity->getGroup() << endl;
}