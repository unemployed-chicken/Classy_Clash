#pragma once
#include "raylib.h"
#include "Prop.h"
#include <string>
#include <vector>
#include <map>
using std::map;
using std::string;
using std::vector;

constexpr float x_boundry{ 162.5 };
constexpr float y_boundry{ 128.5 };
constexpr float map_width{ 1679.0 };
constexpr float map_height{ 1586.0 };


class Map {
	Texture2D Texture;
	Vector2 Position{};
	Rectangle Boundries{ x_boundry, y_boundry, map_width, map_height };
	vector<Prop> Props;

public:
	Map(map<string, Texture2D> textures) {
		Texture = textures["island_map"];
		Props = generateAllProps(textures);
	}

	Texture2D getTexture();
	Vector2 getPosition();
	void setPosition(Vector2 pos);
	Rectangle getBoundries();
	vector<Prop> getProps();
	vector<Prop> generateAllProps(map<string, Texture2D> textures);
	void renderAllProps(Vector2 knight_pos);
};

