#include "Map.h"

Vector2 Map::getPosition() { return Position; }
void Map::setPosition(Vector2 pos) { Position = pos; }
Rectangle Map::getBoundries() { return Boundries; }
Texture2D Map::getTexture() { return Texture; }
vector<Prop> Map::getProps() { return Props; }

vector<Prop> Map::generateAllProps(map<string, Texture2D> textures) {
    return vector<Prop> {
        Prop(textures["pond"], "pond", Vector2{ 865.f, 895.f }),
        Prop(textures["pond"], "pond", Vector2{1487.f, 442.f}),
        Prop(textures["pond"], "pond", Vector2{1792.f, 1621.f}),
        Prop(textures["tree"], "tree", Vector2{650.f, 500.f}),
        Prop(textures["tree"], "tree", Vector2{1350.f, 1612.f}),
        Prop(textures["stump"], "stump",Vector2{ 1700.f, 617.f }),
        Prop(textures["stump"], "stump",Vector2{ 712.f, 1301.f }),
        Prop(textures["stump"], "stump", Vector2{ 1009.f, 1489.f }),
        Prop(textures["challice"], "challice", Vector2{ 1089.f, 1181.f }, 3),
        Prop(textures["sign"], "sign", Vector2{1585.3f, 1254.3f}, 3),
        Prop(textures["bush"], "bush", Vector2{ 512.f, 1782.f }),
        Prop(textures["bush"], "bush", Vector2{ textures["bush"].width * 4 + 512.f, 1782.f })
    };
}

void Map::renderAllProps(Vector2 knight_pos) {
    // Does this need to be a ref?
    for (Prop prop : Props) { 
        prop.render(knight_pos);
    }
}