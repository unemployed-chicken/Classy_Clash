#pragma once
#include "Knight.h"
#include "Enemy.h"
#include "Map.h"

class Controller {
public:
    void checkUserInput(Knight& knight, Map world_map);
    void moveAllAiCharacters(Enemy enemies[], Map& world_map, float dT, int array_size);
    void moveAiCharacter(Enemy& e, Map world_map, float dT); 
    void boundryCheck(Vector2& pos, Map world_map);
    bool collisionCheck(Vector2 pos, Map world_map, Character c);
    void knightAttack(Knight knight, Enemy enemies[], int array_size);
    void damageCheck(Rectangle weaponCollisionRec, Character& defender, float damage = 3.0f);
    void damageCheck(Enemy& e);
    void enemiesAttack(Enemy enemies[], int array_size);
    Vector2 calculateNewPosition(Vector2 direction, Character c, Map world_map);
};

