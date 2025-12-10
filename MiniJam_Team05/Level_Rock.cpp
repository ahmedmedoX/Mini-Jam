#include "Level_Rock.h"

Level_Rock::Level_Rock(b2World& world, Texture* Background_Texture) :
	Level(world, Background_Texture)
{
    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(384 + 48, 64 + 80 + 64)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 128.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    //std::unique_ptr<GameObject> Key1 = std::make_unique<GameObject>(
    //    Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 400)),
    //    world, 64.f / Utilities::PIXELS_PER_UNIT, 128.f / Utilities::PIXELS_PER_UNIT,
    //    2.0f, false, KEY);

    Keys.push_back(std::make_unique<Key>(
        world, Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 400))));
    //Environment.push_back(std::move(Key2));

    //Environment.push_back(std::make_unique<GameObject>(
    //    Utilities::Convert_SFML_Box2D_Space(Vector2f(384 + 48, 64 + 80 + 64)),
    //    world, 64.f / Utilities::PIXELS_PER_UNIT, 128.f / Utilities::PIXELS_PER_UNIT,
    //    2.0f, false, KEY));
}

Level_Rock::~Level_Rock() {}