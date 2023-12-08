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

        Difficulty(shared_ptr<Player> _player, shared_ptr<EntityHandler> _entityHandler){
            player = _player;
            
            //set various types of enemies (800 is approximately outside the play area)
            shared_ptr<Npc> npc1 = make_shared<Npc>(Vector2d(-800, 500), 70, _player);
            shared_ptr<Npc> npc2 = make_shared<Npc>(Vector2d(-800, -500), 70, _player);
            shared_ptr<Npc> npc3 = make_shared<Npc>(Vector2d(-600, -800), 70, _player);
            shared_ptr<Npc> npc4 = make_shared<Npc>(Vector2d(-500, -800), 70, _player);
            shared_ptr<Npc> npc5 = make_shared<Npc>(Vector2d(500, -800), 70, _player);
            shared_ptr<Npc> npc6 = make_shared<Npc>(Vector2d(600, -800), 70, _player);
            shared_ptr<Npc> npc7 = make_shared<Npc>(Vector2d(800, 500), 70, _player);
            shared_ptr<Npc> npc8 = make_shared<Npc>(Vector2d(800, 600), 70, _player);

            shared_ptr<SniperEnemy> sniper1 = make_shared<SniperEnemy>(Vector2d(600, 600), 70, _player, _entityHandler);
            shared_ptr<SniperEnemy> sniper2 = make_shared<SniperEnemy>(Vector2d(-600, 600), 70, _player, _entityHandler);
            shared_ptr<SniperEnemy> sniper3 = make_shared<SniperEnemy>(Vector2d(-600, -600), 70, _player, _entityHandler);
            shared_ptr<SniperEnemy> sniper4 = make_shared<SniperEnemy>(Vector2d(600, -600), 70, _player, _entityHandler);
            

            //diff 1
            vec1.push_back(npc1);
            //diff 2
            vec2.push_back(sniper1);
            //diff 3
            vec3.push_back(npc1);
            vec3.push_back(npc2);
            vec3.push_back(npc3);
            //diff 4
            vec4.push_back(sniper2);
            vec4.push_back(npc2);
            vec4.push_back(npc3);
            vec4.push_back(sniper4);
            //diff 5
            vec5.push_back(npc1);
            //diff 6
            vec6.push_back(npc1);
            //diff 7
            vec7.push_back(npc1);
            //diff 8
            vec8.push_back(npc1);
            //diff 9
            vec9.push_back(npc1);
            //diff 10
            vec10.push_back(npc1);

            enemiesByDifficulty[1] = vec1;
            enemiesByDifficulty[2] = vec2;
            enemiesByDifficulty[3] = vec3;
            enemiesByDifficulty[4] = vec4;
            enemiesByDifficulty[5] = vec5;
            enemiesByDifficulty[6] = vec6;
            enemiesByDifficulty[7] = vec7;
            enemiesByDifficulty[8] = vec8;
            enemiesByDifficulty[9] = vec9;
            enemiesByDifficulty[10] = vec10;
        }
        vector<shared_ptr<Entity>> getEnemiesByDifficulty(size_t _difficulty){
            return enemiesByDifficulty[_difficulty];
        }

    private:
        shared_ptr<Player> player;
        vector<shared_ptr<Entity>> vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8, vec9, vec10;
        unordered_map<size_t, vector<shared_ptr<Entity>>> enemiesByDifficulty;

};


#endif