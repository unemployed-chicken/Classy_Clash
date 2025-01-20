#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <string>

extern const int window_dimensions[2];
extern const bool debugging;

class Character {
protected:
    std::string Name{};
    Texture2D Idle_Texture{};
    Texture2D Run_Texture{};
    Texture2D Active_Texture{};
    Vector2 Screen_Position{}; // The Vector used to draw the character to the screen. In the case of this game, always in the center.
    Vector2 World_Position{}; // The Vector used to indicate the characters position in the world.
    Rectangle collisionRec{};
    bool IsAlive{ true };
    float Health{};
    int Width{};
    int Height{};

    float run_time{};
    const float update_time{ 1.0f / 12.0f };
    int frame{};
    float left_right{ 1.0f };
    float speed{ 4.0f };
    float scale{ 4.0f };
    int sprite_sheet_count{ 6 };

public:
    std::string getName();
    float getRunTime();
    void increaseRunTime(const float dT);
    float getUpdateTime();
    int getFrame();
    float getLeftRight();
    void setLeftRight(float i);
    float getWorldPositionX();
    float getWorldPositionY();
    Vector2 getWorldPos();
    Vector2 getScreenPos();
    void setScreenPos(float x, float y);
    float getSpriteWidth();
    float getSpriteHeight();
    void setPosition(Vector2 pos);
    void isMoving(const bool isMoving);
    Texture2D getActiveTexture();
    void setWorldPos(Vector2 world_pos);
    void animateCharacter(const float dT);
    int getSpeed();
    float getHealth();
    void takeDamage(float damage);
    Rectangle getCollisionRec();
    bool getIsAlive() const;
    void setIsAlive();
    void setCollisionRec();
    virtual void drawCharacter();

    Character(Texture2D idle_texture, Texture2D run_texture, float window_width, float window_height, float health, std::string name) :
            Idle_Texture(idle_texture),
            Run_Texture(run_texture),
            Active_Texture(idle_texture), 
            Health(health),
            Name(name) {

        Width = Active_Texture.width / sprite_sheet_count;
        Height = Active_Texture.height;

        Screen_Position = Vector2{
            (window_width * .5f) - scale * (.5f * Width),
            (window_height * .5f) - scale * (.5f * Height)
        };

        setCollisionRec();
    }

    Character() {};
};

