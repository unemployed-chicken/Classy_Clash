#include "Controller.h"

#include <iostream>
using std::cout;

extern float attacks_per_second;

void Controller::checkUserInput(Knight& knight, Map world_map) {
    Vector2 direction{};
    if (IsKeyDown(KEY_LEFT)) { direction.x -= 1.0; }
    if (IsKeyDown(KEY_RIGHT)) { direction.x += 1.0; }
    if (IsKeyDown(KEY_UP)) { direction.y -= 1.0; }
    if (IsKeyDown(KEY_DOWN)) { direction.y += 1.0; }

    if (Vector2Length(direction) != 0.0) {
        Vector2 new_position = calculateNewPosition(direction, knight, world_map);
        
        if (!collisionCheck(new_position, world_map, knight)) {
            knight.setWorldPos(new_position);
            knight.setCollisionRec();
        }
        
        direction.x < 0.f ? knight.setLeftRight(-1.0) : knight.setLeftRight(1.0);
        knight.isMoving(true);
    }
    else {
        knight.isMoving(false);
    }
}

void Controller::moveAllAiCharacters(Enemy enemies[], Map& world_map, float dT, int array_size) {
    for (int i = 0; i < array_size; ++i) {
        if (enemies[i].getIsAlive()) {
            moveAiCharacter(enemies[i], world_map, dT);
        }
    }
}

void Controller::moveAiCharacter(Enemy& e, Map world_map, float dT) {
    if (e.getIsLockedOn()) {
        Vector2 to_target = e.getToTarget();
        Vector2 new_position = calculateNewPosition(to_target, e, world_map);

        if (Vector2Length(new_position) != 0.0 && Vector2Length(e.getToTarget()) > e.getRadius()) {
            if (!collisionCheck(new_position, world_map, e)) {
                e.setWorldPos(new_position);
            };
            e.setCollisionRec();
            to_target.x < 0.f ? e.setLeftRight(-1.0) : e.setLeftRight(1.0);
            e.isMoving(true);
        }
        else if (Vector2Length(e.getToTarget()) < e.getRadius()) {
            e.isMoving(false);
        }
    }
    else {
        e.isMoving(false);
    }

    e.tick(dT);
   
}


Vector2 Controller::calculateNewPosition(Vector2 direction, Character c, Map world_map) {
    Vector2 new_position = Vector2Add(c.getWorldPos(), Vector2Scale(Vector2Normalize(direction), c.getSpeed()));
    boundryCheck(new_position, world_map);
    return new_position;
}

void Controller::boundryCheck(Vector2& pos, Map world_map) {
    if (pos.x < world_map.getBoundries().x) {
        pos.x = world_map.getBoundries().x;
    } 
    else if (pos.x > (world_map.getBoundries().x + world_map.getBoundries().width)) {
        pos.x = world_map.getBoundries().x + world_map.getBoundries().width;
    }
    if (pos.y < world_map.getBoundries().y) {
        pos.y = world_map.getBoundries().y;
    }
    else if (pos.y > (world_map.getBoundries().y + world_map.getBoundries().height)) {
        pos.y = (world_map.getBoundries().y + world_map.getBoundries().height);
    }

}

bool Controller::collisionCheck(Vector2 pos, Map world_map, Character c) {
    // Below a rectangle for the knights collision box and offsets for screen position
    Rectangle character_rec{ 
        pos.x + window_dimensions[0] / 2, // Offsets difference between world position and screen width
        pos.y + window_dimensions[1] / 2, // Offsets difference between world position and screen height
        c.getSpriteWidth(), 
        c.getSpriteHeight() 
    };
    for (Prop prop : world_map.getProps()) {
        if (CheckCollisionRecs(character_rec, prop.getCollisionRec())) {
            std::cout << c.getName() << " ran into " << prop.getName() << '\n';
            return true;
        };
    };
    return false;
}

void Controller::knightAttack(Knight knight, Enemy enemies[], int array_size) {
    for (int i = 0; i < array_size; ++i) {
        damageCheck(knight.getWeaponCollisionRec(), enemies[i]);
    }
}


void Controller::damageCheck(Rectangle attack_object, Character& defender, float damage) {      
    if (CheckCollisionRecs(attack_object, defender.getCollisionRec())) {
        std::cout << defender.getName() << " was hurt!\n";
        defender.takeDamage(damage);
        if (defender.getHealth() <= 0) {
            defender.setIsAlive();
            defender.setScreenPos(0, 0);
            defender.setCollisionRec();
        }
    };
}

void Controller::damageCheck(Enemy& e) {
    if (e.getTarget() -> getDamagedCooldown() >= 1.0f / attacks_per_second && 
                CheckCollisionRecs(e.getCollisionRec(), e.getTarget()->getCollisionRec())) {
        
        damageCheck(e.getCollisionRec(), (*e.getTarget()), e.getDPS()/attacks_per_second);
        e.getTarget() -> zeroDamagedCooldown();
    };
}

void Controller::enemiesAttack(Enemy enemies[], int array_size) {
    for (int i = 0; i < array_size; ++i) {
        damageCheck(enemies[i]);
    }
}
