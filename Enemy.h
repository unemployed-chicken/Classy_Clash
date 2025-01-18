#pragma once
#include "Character.h"
#include "Knight.h"

extern const int window_dimensions[2];

class Enemy : public Character {
    Knight* Target{};
public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, float pos_x, float pos_y, float spd, std::string name = "goblin") 
            :Character(idle_texture, run_texture, window_dimensions[0], window_dimensions[1], name) {
        World_Position = Vector2{
            pos_x,
            pos_y
        };
        speed = spd;
    }
    virtual void drawCharacter() override;
    
    bool getIsLockedOn();
    Knight* getTarget();
    void setTarget(Knight* target);
    Vector2 getToTarget();

    void tick(float dT);
    
};

