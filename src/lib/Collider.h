#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vector2d.h"

class Collider {
    public:
        Collider(double radius, Vector2d position) {
            this->position = position;
            this->radius = radius;
        }
        Collider(double radius) {
            this->radius = radius;
            this->position = Vector2d(0, 0);
        }

        bool collidingWith(Collider other) {
            return position.distanceTo(other.position) <= getRadius() + other.getRadius();
        }

        double getRadius() const { return radius; }
        void setRadius(double radius) { this->radius = radius; }

        Vector2d getPosition() const { return position; }
        void setPosition(Vector2d position) { this->position = position; }

        private:
            double radius;
            Vector2d position;
};

#endif