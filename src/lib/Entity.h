#ifndef ENTITY_H
#define ENTITY_H
#include "Point.h"

class Entity { 
    public:
        virtual void draw() = 0;
        virtual void update() = 0;
};

#endif