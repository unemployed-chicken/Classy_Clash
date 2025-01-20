#include "Knight.h"

void Knight::render(float dT) {
    setTint();
    incrementDamagedCooldown(dT);
	animateCharacter(dT);
	drawCharacter();
    drawWeapon();
    if (debugging) {
        DrawRectangleLines(
            collisionRec.x,
            collisionRec.y,
            collisionRec.width,
            collisionRec.height,
            BLACK
        );
    }
}

Rectangle Knight::getWeaponCollisionRec() { return WeaponCollisionRec; }
Color Knight::getTint() { return Tint; }
void Knight::setTint() { DamagedCooldown < 0.35f ? Tint = RED : Tint = WHITE; }
float Knight::getDamagedCooldown() const { return DamagedCooldown; }
void Knight::incrementDamagedCooldown(float dT) { DamagedCooldown += dT; }
void Knight::zeroDamagedCooldown() { DamagedCooldown = 0.0f; }

void Knight::drawWeapon() {
    Vector2 origin = getWeaponOrigin();
    Vector2 offset = getWeaponOffset();
    generateWeaponCollisionRec(offset);
    float rotation = IsKeyDown(KEY_F) ? 35.0f * left_right : 0.0f;
    
    Rectangle source{ 0.0f, 0.0f, (left_right * static_cast<float>(Weapon.width)), static_cast<float>(Height) };
    Rectangle dest{ 
        Screen_Position.x + offset.x, Screen_Position.y + offset.y,
        scale * static_cast<float>(Weapon.width), scale * static_cast<float>(Height) 
    };
    DrawTexturePro(Weapon, source, dest, origin, rotation, WHITE);
}

Vector2 Knight::getWeaponOrigin() {
    Vector2 offset{};
    if (left_right > 0) {
        offset = { 35.0f, 55.0f };
        return Vector2{ 0.f, static_cast<float>(Weapon.height) * scale };
    }
    else {
        offset = { 25.0f, 55.0f };
        return Vector2{ static_cast<float>(Weapon.width) * scale, static_cast<float>(Weapon.height) * scale };
    }
}

Vector2 Knight::getWeaponOffset() {
    if (left_right > 0) {
        return Vector2{ 35.0f, 55.0f };
    }
    else {
        return Vector2{ 25.0f, 55.0f };
    }
}

void Knight::drawCharacter() {
    Rectangle source{ (float)(frame % 6) * Width, .0f, (left_right * static_cast<float>(Width)), static_cast<float>(Height) };
    Rectangle dest{ Screen_Position.x, Screen_Position.y, scale * static_cast<float>(Width), scale * static_cast<float>(Height) };
    DrawTexturePro(Active_Texture, source, dest, Vector2{}, 0.0, Tint);
}


void Knight::generateWeaponCollisionRec(Vector2 offset) {
    if (left_right > 0) {
       WeaponCollisionRec = {
           Screen_Position.x + offset.x,
           Screen_Position.y + offset.y - (Weapon.height * scale),
           scale * static_cast<float>(Weapon.width),
           scale * static_cast<float>(Height)
        };
    }
    else {
        WeaponCollisionRec = {
           Screen_Position.x + offset.x - (Weapon.height * scale),
           Screen_Position.y + offset.y - (Weapon.height * scale),
           scale * static_cast<float>(Weapon.width), 
           scale * static_cast<float>(Height)
        };
    }
   

    if (debugging) {
        DrawRectangleLines(
            Screen_Position.x + offset.x,
            Screen_Position.y + offset.y - (Weapon.height * scale),
            scale * static_cast<float>(Weapon.width) * left_right,
            scale * static_cast<float>(Height),
            RED
        );
    }
    
}

