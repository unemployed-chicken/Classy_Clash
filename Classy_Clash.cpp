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

// General Properties
const bool debugging{ false };
float world_scale{ 4.0 };
float attacks_per_second{ 2.0f };
constexpr long number_of_enemies{ 5 };

// Methods
map<string, Texture2D> generateTextures();
void unloadAllTextures(map<string, Texture2D> textures);
void displayHealth(Knight knight, Texture2D hearts);
void assignTargetToEnemies(Enemy enemies[], Knight& knight);
bool areEnemiesPresent(Enemy enemies[]);

// Debug Only
void displayCoordinates(Vector2 map, Knight knight, Enemy e[]);

int main()
{
    InitWindow(window_dimensions[0], window_dimensions[1], "Classy Clash");
    SetTargetFPS(targetFps);

    Vector2 map_pos{ };
    map<string, Texture2D> textures = generateTextures();
    // Background Textures
    Map world_map{ textures }; // WARNING: This will create a new texture if key does not exist
    
    // Create Character:
    Knight knight = Knight(textures["knight_idle"], textures["knight_run"], textures["sword"], window_dimensions[0], window_dimensions[1]);

    Enemy enemies[number_of_enemies]{
        Enemy(textures["goblin_idle"], textures["goblin_run"], 400.f, 500.f, 3.0f, 3.0f, "goblin_1"), // Good
        Enemy(textures["goblin_idle"], textures["goblin_run"], 1500.f, 1500.f, 3.0f, 3.0f, "goblin_2"), // Move Right 
        Enemy(textures["goblin_idle"], textures["goblin_run"], 1750.f, 1650.f, 3.0f, 3.0f, "goblin_3"), // Good
        Enemy(textures["slime_idle"], textures["slime_run"], 1750.f, 200.f, 3.0f, 2.0f, "slime_1"), // Good 
        Enemy(textures["slime_idle"], textures["slime_run"], 512.f, 1550, 3.0f, 2.0f, "slime_2") // Good
    };

    // Assign Knight as target of all enemies
    assignTargetToEnemies(enemies, knight);

    // Create Contorller:
    Controller controller;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        controller.checkUserInput(knight, world_map);
        map_pos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw Map
        DrawTextureEx(world_map.getTexture(), map_pos, 0, world_scale, WHITE);

        // Draw Prop
        world_map.renderAllProps(knight.getWorldPos());

        if (!areEnemiesPresent(enemies)) {
            DrawText("You Win!", window_dimensions[0] * .25, window_dimensions[1] / 2 - 25, 50, WHITE);
        }
        else if (knight.getIsAlive()) {
            // Time since last frame
            const float dT{ GetFrameTime() };

            // Move and Draw all enemies 
            // Small Bug: Drawing characters should occur only after damage calculation. Leaving as this isn't critical to my practice
            controller.moveAllAiCharacters(enemies, world_map, dT, number_of_enemies);

            // User Attack Phase
            if (IsKeyPressed(KEY_F)) {
                controller.knightAttack(knight, enemies, number_of_enemies);
            }

            // Enemies attack Phase
            controller.enemiesAttack(enemies, number_of_enemies);

            // Draw Character
            knight.render(dT);
            if (!debugging) {
                displayHealth(knight, textures["health"]);
            }
            else {
                displayCoordinates(map_pos, knight, enemies);
            }
        }
        else {
            DrawText("Game Over!", window_dimensions[0] * .15 , window_dimensions[1] / 2 - 25, 50, WHITE);
            if (!debugging) {
                displayHealth(knight, textures["health"]);
            }
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
        {"slime_idle", LoadTexture("characters\\slime_idle_spritesheet.png")},
        {"slime_run", LoadTexture("characters\\slime_run_spritesheet.png")},
        {"island_map", LoadTexture("nature_tileset\\world_map.png")},
        {"stump", LoadTexture("nature_tileset\\stump.png")},
        {"tree", LoadTexture("nature_tileset\\tree.png")},
        {"sign", LoadTexture("nature_tileset\\Sign.png")},
        {"challice", LoadTexture("nature_tileset\\challice.png")},
        {"bush", LoadTexture("nature_tileset\\Bush.png")},
        {"pond", LoadTexture("nature_tileset\\pond.png")},
        {"sword", LoadTexture("characters\\weapon_sword.png")},
        {"health", LoadTexture("characters\\health.png")}
    };

    return textures;
}


void unloadAllTextures(map<string, Texture2D> textures) {
    for (auto itr = textures.begin(); itr != textures.end(); itr++) {
        UnloadTexture((*itr).second);
    }
}


void displayCoordinates(Vector2 map, Knight knight, Enemy e[]) {
    string mapXCoordinate = "Goblin X: ";
    mapXCoordinate.append(std::to_string(e[0].getScreenPos().x));
    DrawText(mapXCoordinate.c_str(), 25, 25, 25, WHITE);

    string YbaseString = "Goblin Y: ";
    YbaseString.append(std::to_string(e[0].getScreenPos().y));
    DrawText(YbaseString.c_str(), 25, 50, 25, WHITE);

    //char knightXCoorBase[] = "Knight X: ";
    //char knightXCoor[50];
    //sprintf_s(knightXCoor, "%s%f", knightXCoorBase, knight.getWorldPositionX());
    //DrawText(knightXCoor, 25, 75, 25, WHITE);

    //char knightYCoorBase[] = "Knight Y: ";
    //char knightYCoor[50];
    //sprintf_s(knightYCoor, "%s%f", knightYCoorBase, knight.getWorldPositionY());
    //DrawText(knightYCoor, 25, 100, 25, WHITE);

    char knightCollisionRec[] = "Knight Health: ";
    char knightCol[50];
    sprintf_s(knightCol, "%s%f", knightCollisionRec, knight.getHealth());
    DrawText(knightCol, 25, 75, 25, WHITE);

    string enemyCollisionX = "Enemies Exist: ";
    enemyCollisionX.append(std::to_string(areEnemiesPresent(e)));
    DrawText(enemyCollisionX.c_str(), 25, 100, 25, WHITE);

    //string enemyCollisionY = "EnemyCollision Y: ";
    //enemyCollisionY.append(std::to_string(map.y));
    //DrawText(enemyCollisionY.c_str(), 25, 125, 25, WHITE);
}

void displayHealth(Knight knight, Texture2D hearts) {
    float row{}; 

    if (knight.getHealth() >= 30) { row = 0.0f; }
    else if (knight.getHealth() >= 25) { row = 1.0f; }
    else if (knight.getHealth() >= 20) { row = 2.0f; }
    else if (knight.getHealth() >= 15) { row = 3.0f; }
    else if (knight.getHealth() >= 10) { row = 4.0f; }
    else if (knight.getHealth() >= 5) { row = 5.0f; }
    else { row = 6; }

    Rectangle source{ 0.0f, (hearts.height / 7) * row, hearts.width, hearts.height / 7};
    Rectangle dest{ 10.0f, 10.0f, hearts.width * world_scale, (hearts.height / 7) * world_scale };
    DrawTexturePro(hearts, source, dest, Vector2{}, 0.0, WHITE);
}


// Refactor: Make Enemy constructor take Knight and pass in on creation to save on extra loop
void assignTargetToEnemies(Enemy enemies[], Knight& knight) {
    for (int i = 0; i < number_of_enemies; ++i) {
        enemies[i].setTarget(&knight);
    }
}

bool areEnemiesPresent(Enemy enemies[]) {
    for (int i = 0; i < number_of_enemies; ++i) {
        if (enemies[i].getIsAlive()) {
            return true;
        }
    }
    return false;
}