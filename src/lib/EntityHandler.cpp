#include "EntityHandler.h"
#include <iostream>

EntityHandler::EntityHandler() {
    enemyCount = 0;
}

void EntityHandler::addGroup(string newGroup, vector<string> collisions) {
    entities[newGroup] = vector<shared_ptr<Entity>>();
    for(const auto& pair : entities) {
        bool found = false;
        for(string group : collisions) {
            if(pair.first == group) {
                found = true;
                break;
            }
        }
        if (found) {
            collisionMatrix[pair.first][newGroup] = true;
            collisionMatrix[newGroup][pair.first] = true;
        } else {
            collisionMatrix[pair.first][newGroup] = false;
            collisionMatrix[newGroup][pair.first] = false;
        }
    }
} 

void EntityHandler::addEntity(shared_ptr<Entity> entity, string group) {
    entities[group].push_back(entity);
    if(entity->isEnemy()){
        enemyCount++;
        std::cout << "enemycount: " << enemyCount << "\n";
    }
}

void EntityHandler::updateAll() {
    for(const auto& pair : entities) {
        for(shared_ptr<Entity> entity : pair.second) {
            entity->update();
        }
    }
    
}

void EntityHandler::drawAll() {
    for(const auto& pair : entities) {
        for(shared_ptr<Entity> entity : pair.second) {
            entity->draw();
        }
    }
}

void EntityHandler::addCollision(string group1, string group2) {
    collisionMatrix[group1][group2] = true;
    collisionMatrix[group2][group1] = true;
}

void EntityHandler::checkCollisions() {
    // Go through every pair of groups
    for(const auto& pair1 : entities) {
        for(const auto& pair2 : entities) {

            // check if each pair is true in the matrix
            if(collisionMatrix[pair1.first][pair2.first]) {

                //go through each entity in two group and check if they are colliding
                for(shared_ptr<Entity> e1 : pair1.second) {
                    for(shared_ptr<Entity> e2 : pair2.second) {
                        if(e1 != e2 && e1->getCollider().collidingWith(e2->getCollider())) {
                            e1->handleCollision(e2);
                        }
                    }
                }
            }
        }
    }
    clearUnalive();
}

void EntityHandler::clearUnalive(){
    for(auto& pair : entities) {
        for(size_t i = 0; i<pair.second.size(); ++i) {
            if(pair.second.at(i)->alive() == false){
                    if(pair.second.at(i)->isEnemy()){
                        enemyCount--;
                        std::cout << "enemycount: " << enemyCount << "\n";
                    }
                pair.second.erase(pair.second.begin() + i);
            }
        }
    }
}

void EntityHandler::clearAllEntities() {
    for(auto& pair : entities) {
        for(size_t i = 0; i<pair.second.size(); ++i) {
            if(pair.second.at(i)->isEnemy()){
                enemyCount--;
            }
            pair.second.erase(pair.second.begin() + i);
        }
    }
}

void EntityHandler::print() {
    for(auto& pair : entities) {
        for(size_t i = 0; i < pair.second.size(); i++) {
            cout << pair.second.at(i)->getGroup() << endl;
        }
    }
}
