// Classy_Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Window Properties 
const int window_dimensions[2]{ 384 , 384 }; // Width * Height
const int targetFps{ 60 };

void drawAllBackgrounds(const Texture2D map);

int main()
{
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");
    SetTargetFPS(targetFps);

    // Background Textures
    Texture2D island_map = LoadTexture("nature_tileset\\world_map.png");
    Vector2 map_pos{ 0.0, 0.0 };
    float speed{ 4.0 };

    while (!WindowShouldClose()) {
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
        }

        // To be refactored
        // drawAllBackgrounds(island_map);
        DrawTextureEx(island_map, map_pos, 0, 4.0, WHITE);

        EndDrawing();
    }

    UnloadTexture(island_map);
    CloseWindow();
}


void drawAllBackgrounds(const Texture2D map) {
    Vector2 map_vect{ 0.0, 0.0 };
    DrawTextureEx(map, map_vect, 0, 4.0, WHITE);
}
