#include "Level_Forest.h"

Level_Forest::Level_Forest(b2World& world) :
    Level(world, &SpriteLoader::getTexture(SpriteType::Level2))
{
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 64 * 2.5f)),
        world, 128.f / Utilities::PIXELS_PER_UNIT, 128.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Level_Key = make_unique<Key>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 200)));

    Level_Door = make_unique<Door>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 500)));
}

Level_Forest::~Level_Forest() {}