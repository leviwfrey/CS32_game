#include "Entity.h"
#include "EntityHandler.h"
#include <iostream>


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
Player::Player(shared_ptr<EntityHandler> entityHandler, Vector2d position) {
    this->pos = position;
    this->vel = Vector2d(0, 0);
    this->rot = controller.getMousePos().difference(pos).getAngle();
    this->group = "Players";
    this->collider = Collider(50, pos);
    this->entityHandler = entityHandler;
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
}

void Player::handleCollision(shared_ptr<Entity> entity) {
    cout << entity->getGroup();
}

// NPC

Npc::Npc(Vector2d position, double size) {
    this->pos = position;
    this->size = size;
    this->collider = Collider(40);
    this->rot = 0;
}

void Npc::draw() {
    Vector2d::drawPoly(pos, body, rot);
}

void Npc::update() {
}

void Npc::handleCollision(shared_ptr<Entity> entity) {
    cout << entity->getGroup();
}