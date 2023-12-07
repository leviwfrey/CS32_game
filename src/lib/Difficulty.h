#ifndef DIFFICULTY_H
#define DIFFICULTY_H
#include <unordered_map>
#include <vector>

#include <Entity.h>
#include <memory>
#include <Vector2d.h>

using namespace std;


class Difficulty {
    public:
        // struct EnemyVariant{             
        // int myNum;         
        // string myString;   
        // };       

        Difficulty(shared_ptr<Player> _player){
            player = _player;
            
            //set various types of enemies
            shared_ptr<Npc> enemy1 = make_shared<Npc>(Vector2d(-300, 300), 70, player);
            shared_ptr<Npc> enemy2 = make_shared<Npc>(Vector2d(-300, -300), 70, player);
            shared_ptr<Npc> enemy3 = make_shared<Npc>(Vector2d(300, 300), 70, player);

            //diff 1
            vec1.push_back(enemy1);
            //diff 2
            vec2.push_back(enemy1);
            vec2.push_back(enemy2);
            //diff 3
            vec3.push_back(enemy1);
            vec3.push_back(enemy2);
            vec3.push_back(enemy3);

            enemiesByDifficulty[1] = vec1;
            enemiesByDifficulty[2] = vec2;
            enemiesByDifficulty[3] = vec3;
        }
        vector<shared_ptr<Entity>> getEnemiesByDifficulty(size_t _difficulty){
            return enemiesByDifficulty[_difficulty];
        }

    private:
        shared_ptr<Player> player;
        vector<shared_ptr<Entity>> vec1, vec2, vec3;
        unordered_map<size_t, vector<shared_ptr<Entity>>> enemiesByDifficulty;

};


#endif