// Classy_Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Window Properties 
const int window_dimensions[2]{ 384 , 384 }; // Width * Height
const int targetFps{ 60 };

void drawAllBackgrounds(const Texture2D map);

class Character {
    Texture2D Idle_Texture;
    Texture2D Run_Texture;
    Texture2D Active_Texture;
    Vector2 Sprit_Position;

    float run_time{};
    const float update_time{ 1.0 / 12.0 };
    int frame{};
    float left_right{ 1.0f };

public:
    float getRunTime() { return run_time; }
    void increaseRunTime(const float dT) { run_time += dT; };
    float getUpdateTime() { return update_time; }
    int getFrame() { return frame; }
    float getLeftRight() { return left_right; }
    void setLeftRight(float i) { left_right = i; }
    float getSpritePositionX() { return Sprit_Position.x; }
    float getSpritePositionY() { return Sprit_Position.y; }
    float getSpriteWidth() { return ( Active_Texture.width / 6.0f); }
    float getSpriteHeight() { return Active_Texture.height; }
    void setPosition(Vector2 pos) { Sprit_Position = pos; }
    void isMoving(const bool isMoving) { isMoving ? Active_Texture = Run_Texture : Active_Texture = Idle_Texture; }
    Texture2D getActiveTexture() { return Active_Texture; }
    
    void animateCharacter(const float dT) {
        run_time += dT;
        if (run_time >= update_time) {
            run_time = 0.0;
            ++frame;
        }
    }

    void drawCharacter() {
        Rectangle source{ (frame % 6) * Active_Texture.width / 6, .0f, (left_right * Active_Texture.width / 6.0f), Active_Texture.height }; // correct
        Rectangle dest{ Sprit_Position.x, Sprit_Position.y, 4.0f * Active_Texture.width / 6.0f, 4.0f * Active_Texture.height };
        DrawTexturePro(Active_Texture, source, dest, Vector2{}, 0.0, WHITE);
    }

    Character(Texture2D idle_texture, Texture2D run_texture) {
        Idle_Texture = idle_texture;
        Run_Texture = run_texture;
        Active_Texture = idle_texture;
        
        Sprit_Position = Vector2 {
            (window_dimensions[0] * .5f) - 4.0f * (.5f * Active_Texture.width / 6.f),
            (window_dimensions[1] * .5f) - 4.0f * (.5f * Active_Texture.height)
        };
    }
};

int main()
{
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");
    SetTargetFPS(targetFps);

    // Background Textures
    Texture2D island_map = LoadTexture("nature_tileset\\world_map.png");
    Vector2 map_pos{ 0.0, 0.0 };
    float speed{ 4.0 };

    // Create Character:
    Texture2D knight_idle = LoadTexture("characters\\knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters\\knight_run_spritesheet.png");
    Character knight_char = Character(knight_idle, knight_run);

    // Create Goblin: 
    Texture2D goblin_idle = LoadTexture("characters\\goblin_idle_spritesheet.png");
    Texture2D goblin_run = LoadTexture("characters\\goblin_run_spritesheet.png");
    Character goblin_char = Character(goblin_idle, goblin_run);

    while (!WindowShouldClose()) {
        // Time since last frame
        const float dT{ GetFrameTime() };

        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        if (IsKeyDown(KEY_LEFT)) { direction.x -= 1.0; }
        if (IsKeyDown(KEY_RIGHT)) { direction.x += 1.0; }
        if (IsKeyDown(KEY_UP)) { direction.y -= 1.0; }
        if (IsKeyDown(KEY_DOWN)) { direction.y += 1.0; }
        if (Vector2Length(direction) != 0.0) {
            // Set mapPos = map_pos - direction
            map_pos = Vector2Subtract(map_pos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? knight_char.setLeftRight(-1.0) : knight_char.setLeftRight(1.0);
            knight_char.isMoving(true);
        }
        else {
            knight_char.isMoving(false);
        }

        // Update Animation Frame
        knight_char.animateCharacter(dT);
        goblin_char.animateCharacter(dT);

        // To be refactored
        // drawAllBackgrounds(island_map);
        DrawTextureEx(island_map, map_pos, 0, 4.0, WHITE);
        
        // Draw Character
        knight_char.drawCharacter();

        // Draw Goblin
        goblin_char.drawCharacter();



        EndDrawing();
    }

    UnloadTexture(island_map);
    UnloadTexture(knight_idle);
    UnloadTexture(knight_run);
    CloseWindow();
}


void drawAllBackgrounds(const Texture2D map) {
    Vector2 map_vect{ 0.0, 0.0 };
    DrawTextureEx(map, map_vect, 0, 4.0, WHITE);
}
