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
    this->collider = Collider(size/2, pos);
    this->entityHandler = entityHandler;
    this->isAlive = true;
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
}

void Player::handleCollision(shared_ptr<Entity> entity) {
    cout << entity->getGroup();
}

// NPC

Npc::Npc(Vector2d position, double size, shared_ptr<Player> _player) {
    this->pos = position;
    this->size = size;
    this->collider = Collider(size * 0.707, pos); //parameter sets the size of the hitbox
    this->rot = 0;
    this->group = "Enemies";

    p1 = Vector2d(-size/2, size/2);
    p2 = Vector2d(size/2, size/2);
    p3 = Vector2d(size/2, -size/2);
    p4 = Vector2d(-size/2, -size/2);
    body = {p1,p2,p3,p4};
    player = _player;
    this->isAlive = true;
}

void Npc::draw() {
    Vector2d::drawPoly(pos, body, rot);
}

void Npc::update() {
    Vector2d right = Vector2d(speed, 0); // this is a vector at 0 degrees
    rot = player->getPosition().difference(pos).getAngle(); //gets angle from 0 degrees, equal to difference between player and npc
    vel = right.rotate(rot);
    pos.x += vel.x;
    pos.y += vel.y;
    collider.setPosition(pos);
}

void Npc::handleCollision(shared_ptr<Entity> entity) {
    cout << " collided with " << entity->getGroup() << "\n";
    this->isAlive = false;
}