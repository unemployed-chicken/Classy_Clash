#include "Character.h"

std::string Character::getName() { return Name; }
float Character::getRunTime() { return run_time; }
void Character::increaseRunTime(const float dT) { run_time += dT; };
float Character::getUpdateTime() { return update_time; }
int Character::getFrame() { return frame; }
float Character::getLeftRight() { return left_right; }
void Character::setLeftRight(float i) { left_right = i; }
float Character::getWorldPositionX() { return World_Position.x; }
float Character::getWorldPositionY() { return World_Position.y; }
float Character::getSpriteWidth() { return (Active_Texture.width / 6.0f); }
float Character::getSpriteHeight() { return Active_Texture.height; }
void Character::setPosition(Vector2 pos) { World_Position = pos; }
void Character::isMoving(const bool isMoving) { isMoving ? Active_Texture = Run_Texture : Active_Texture = Idle_Texture; }
Texture2D Character::getActiveTexture() { return Active_Texture; }
Vector2 Character::getWorldPos() { return World_Position; }
Vector2 Character::getScreenPos() { return Screen_Position; }
void Character::setWorldPos(Vector2 world_pos) { World_Position = world_pos; }
int Character::getSpeed() { return speed; }

void Character::animateCharacter(const float dT) {
    run_time += dT;
    if (run_time >= update_time) {
        run_time = 0.0;
        ++frame;
    }
}

void Character::drawCharacter() {
    Rectangle source{ (float)(frame % 6) * Width, .0f, (left_right * (float)Width), (float)Height};
    Rectangle dest{ Screen_Position.x, Screen_Position.y, scale * (float) Width, scale * (float) Height};
    DrawTexturePro(Active_Texture, source, dest, Vector2{}, 0.0, WHITE);
}
