#pragma once
#include "Character.h"

constexpr float starting_x_coordinate{ 240.0 };
constexpr float starting_y_coordinate{ 240.0 };

class Knight : public Character {
public: 
    Knight(Texture2D idle_texture, Texture2D run_texture, float window_width, float window_height) 
            :Character(idle_texture, run_texture, window_width, window_height, "knight") {
        World_Position = Vector2{
            starting_x_coordinate,
            starting_y_coordinate
        };
    }
};

