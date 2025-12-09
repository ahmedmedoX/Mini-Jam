#include "Level_Forest.h"

Level_Forest::Level_Forest(b2World& world, std::shared_ptr<sf::Texture> bg) :
    Level(world, bg)
{
    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500 + 48, 64 + 80 + 64)),
        world,
        64 / Utilities::PIXELS_PER_UNIT,
        128 / Utilities::PIXELS_PER_UNIT,
        2.0f,
        false
    ));
}

Level_Forest::~Level_Forest() {}