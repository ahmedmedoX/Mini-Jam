#include "Level_Forest.h"

Level_Forest::Level_Forest(b2World& world, Texture* Background_Texture) :
    Level(world, Background_Texture)
{
    //Environment.push_back(std::make_unique<GameObject>(
    //    Vector2f(384 + 48, 64 + 80 + 64),
    //    world, 64, 128,
    //    2.0f, false));
}

Level_Forest::~Level_Forest() {}