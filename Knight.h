#pragma once
#include "Character.h"

constexpr float starting_x_coordinate{ 240.0 };
constexpr float starting_y_coordinate{ 240.0 };

class Knight : public Character {
    Texture2D Weapon{};
    Rectangle WeaponCollisionRec{};
    float DamagedCooldown{1.0f};
    Color Tint{ WHITE };

public: 
    Knight(Texture2D idle_texture, Texture2D run_texture, Texture2D weapon, float window_width, float window_height) 
            :Character(idle_texture, run_texture, window_width, window_height, 35.0f, "knight") {
        World_Position = Vector2{
            starting_x_coordinate,
            starting_y_coordinate
        };

        Weapon = weapon;
    }

    void render(float dT);
    void drawWeapon();
    Vector2 getWeaponOrigin();
    Vector2 getWeaponOffset();
    void generateWeaponCollisionRec(Vector2 offset);
    Rectangle getWeaponCollisionRec();
    Color getTint();
    void setTint();
    void incrementDamagedCooldown(float dT);
    void zeroDamagedCooldown();
    float getDamagedCooldown() const;
    virtual void drawCharacter() override;
};