// Classy_Clash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include "raylib.h"
#include "raymath.h"
#include "Knight.h"
#include "Enemy.h"
#include "Prop.h"
#include "Map.h"
#include "Controller.h"
using std::string;
using std::map;

// Window Properties 
const int window_dimensions[2]{ 384 , 384 }; // Width * Height
const int targetFps{ 60 };
const bool debugging{ true };
float world_scale{ 4.0 };

map<string, Texture2D> generateTextures();
void unloadAllTextures(map<string, Texture2D> textures);

// Debug Only
void displayCoordinates(Vector2 map, Knight knight, Enemy goblin);

/* Map Bounderies: 
    Left: -162.5 
    Bottom: -1714.5
    Right: - 1841.5
    Top: -128.5
*/



int main()
{
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");
    SetTargetFPS(targetFps);

    Vector2 map_pos{ };
    map<string, Texture2D> textures = generateTextures();
    // Background Textures
    Map world_map{ textures }; // WARNING: This will create a new texture if key does not exist
    
    // Create Character:
    Knight knight = Knight(textures["knight_idle"], textures["knight_run"], window_dimensions[0], window_dimensions[1]);

    // Create Goblin: 
    Enemy goblin = Enemy(textures["goblin_idle"], textures["goblin_run"], 400, 500, 3.0f);
    goblin.setTarget(&knight);

    // Create Contorller:
    Controller controller;

    while (!WindowShouldClose()) {
        // Time since last frame
        const float dT{ GetFrameTime() };

        BeginDrawing();
        ClearBackground(WHITE);

        controller.checkUserInput(knight, world_map);
        map_pos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Update Animation Frame
        knight.animateCharacter(dT);

        // Draw Map
        DrawTextureEx(world_map.getTexture(), map_pos, 0, world_scale, WHITE);

        // Draw Prop
        world_map.renderAllProps(knight.getWorldPos());

        // Move and Draw Goblin
        controller.moveAiCharacter(goblin, world_map, dT);
        
        // Draw Character
        knight.drawCharacter();

        if (debugging) {
            displayCoordinates(map_pos, knight, goblin);
        }
        

        EndDrawing();
    }

    unloadAllTextures(textures);

    CloseWindow();
}

map<string, Texture2D> generateTextures() {
    map<string, Texture2D> textures{
        {"knight_idle", LoadTexture("characters\\knight_idle_spritesheet.png")},
        {"knight_run", LoadTexture("characters\\knight_run_spritesheet.png")},
        {"goblin_idle", LoadTexture("characters\\goblin_idle_spritesheet.png")},
        {"goblin_run", LoadTexture("characters\\goblin_run_spritesheet.png")},
        {"island_map", LoadTexture("nature_tileset\\world_map.png")},
        {"stump", LoadTexture("nature_tileset\\stump.png")},
        {"tree", LoadTexture("nature_tileset\\tree.png")},
        {"sign", LoadTexture("nature_tileset\\Sign.png")},
        {"challice", LoadTexture("nature_tileset\\challice.png")},
        {"bush", LoadTexture("nature_tileset\\Bush.png")},
        {"pond",  LoadTexture("nature_tileset\\pond.png")}
    };

    return textures;
}


void unloadAllTextures(map<string, Texture2D> textures) {
    for (auto itr = textures.begin(); itr != textures.end(); itr++) {
        UnloadTexture((*itr).second);
    }
}

void displayCoordinates(Vector2 map, Knight knight, Enemy goblin) {
    char XbaseString[] = "Map X: ";
    char xCoor[50];
    sprintf_s(xCoor, "%s%f", XbaseString, map.x);
    DrawText(xCoor, 25, 25, 25, WHITE);


    char YbaseString[] = "Map Y: ";
    char yCoor[50];
    sprintf_s(yCoor, "%s%f", YbaseString, map.y);
    DrawText(yCoor, 25, 50, 25, WHITE);

    char knightXCoorBase[] = "Knight X: ";
    char knightXCoor[50];
    sprintf_s(knightXCoor, "%s%f", knightXCoorBase, knight.getWorldPositionX());
    DrawText(knightXCoor, 25, 75, 25, WHITE);

    char knightYCoorBase[] = "Knight Y: ";
    char knightYCoor[50];
    sprintf_s(knightYCoor, "%s%f", knightYCoorBase, knight.getWorldPositionY());
    DrawText(knightYCoor, 25, 100, 25, WHITE);

    char goblinScreenPosXBase[] = "Goblin X: ";
    char goblinScreenX[50];
    sprintf_s(goblinScreenX, "%s%f", goblinScreenPosXBase, goblin.getWorldPositionX());
    DrawText(goblinScreenX, 25, 125, 25, WHITE);

    char goblinScreenPosYBase[] = "Goblin Y: ";
    char goblinScreenY[50];
    sprintf_s(goblinScreenY, "%s%f", goblinScreenPosYBase, goblin.getWorldPositionY());
    DrawText(goblinScreenY, 25, 150, 25, WHITE);

    //char goblinScreenPosXBase[] = "Goblin Screen X: ";
    //char goblinScreenX[50];
    //sprintf_s(goblinScreenX, "%s%f", goblinScreenPosXBase, goblin.getScreenPos().x);
    //DrawText(goblinScreenX, 25, 125, 25, WHITE);

    //char goblinScreenPosYBase[] = "Goblin Screen Y: ";
    //char goblinScreenY[50];
    //sprintf_s(goblinScreenY, "%s%f", goblinScreenPosYBase, goblin.getScreenPos().y);
    //DrawText(goblinScreenY, 25, 150, 25, WHITE);
}
