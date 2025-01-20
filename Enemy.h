#pragma once
#include "Character.h"
#include "Knight.h"


class Enemy : public Character {
    Knight* Target{};
    float DPS{ 10.0f };
    float Radius{ 50.0f };

public:
    Enemy(Texture2D idle_texture, Texture2D run_texture, float pos_x, float pos_y, float health, float spd, std::string name = "goblin")
            :Character(idle_texture, run_texture, window_dimensions[0], window_dimensions[1], health, name) {
        World_Position = Vector2{
            pos_x,
            pos_y
        };
        speed = spd;
    }

    Enemy() {};

    virtual void drawCharacter() override;
    
    bool getIsLockedOn();
    Knight* getTarget();
    void setTarget(Knight* target);
    Vector2 getToTarget();
    float getDPS() const;
    float getRadius() const;

    void tick(float dT);
};

