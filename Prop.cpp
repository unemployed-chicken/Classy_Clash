#include "Prop.h"

void Prop::render(Vector2 knight_pos) {
	Vector2 screen_Position{ Vector2Subtract(World_Position, knight_pos) };
	DrawTextureEx(Texture, screen_Position, 0, Scale, WHITE);
}

Rectangle Prop::getCollisionRec() {	return Collision_Rectangle; }
std::string Prop::getName() { return Name; }