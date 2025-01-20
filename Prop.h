#pragma once
#include "raylib.h"
#include "raymath.h"
#include <string>

class Prop{
	Texture2D Texture{};
	Vector2 World_Position{};
	Rectangle Collision_Rectangle{};
	float Scale{};
	std::string Name{};


public:
	Prop(Texture2D texture, std::string name, Vector2 pos, float scale = 4.0f) : Texture(texture), World_Position(pos), Scale(scale) {
		Name = name;
		Collision_Rectangle = Rectangle{ 
			pos.x, 
			pos.y,
			texture.width * Scale, 
			texture.height * Scale 
		};
	}
	Prop() {};
	void render(Vector2 knight_pos);
	Rectangle getCollisionRec();
	std::string getName();
};

