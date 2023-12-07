#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "Entity.h"

using namespace std;
    

class EntityHandler {
    public:
        EntityHandler();

        void addGroup(string group, vector<string> collisions = {});

        void addEntity(shared_ptr<Entity> entity, string group);
        void addCollision(string group1, string group2);
        void checkCollisions();

        void updateAll();
        void drawAll();
        void clearUnalive();
        void clearAllEntities();
        size_t getEnemyCount(){return enemyCount;}
        void print();
    private:
        unordered_map<string, vector<shared_ptr<Entity>>> entities;
        unordered_map<string, unordered_map<string, bool>> collisionMatrix;
        size_t enemyCount;
};

#endif