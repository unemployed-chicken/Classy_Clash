#pragma once
#include "Knight.h"
#include "Enemy.h"
#include "Map.h"

class Controller {
public:
    void checkUserInput(Knight& knight, Map world_map);
    void moveAiCharacter(Enemy& e, Map world_map, float dT);
    void boundryCheck(Vector2& pos, Map world_map);
    bool collisionCheck(Vector2 pos, Map world_map, Character c);
    Vector2 calculateNewPosition(Vector2 direction, Character c, Map world_map);
};

