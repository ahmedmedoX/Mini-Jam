#include "Level_Lava.h"

Level_Lava::Level_Lava(b2World& world) :
    Level(world,
        &SpriteLoader::getTexture(SpriteType::Level2),
        &SpriteLoader::getTexture(SpriteType::Level2_Background))
{
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 64 * 2.5f)),
        world, 128.f / Utilities::PIXELS_PER_UNIT, 128.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Level_Key = make_unique<Key>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 200)));

    Level_Door = make_unique<Door>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 500)));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 600)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        BOX, 2));

}

Level_Lava::~Level_Lava() {}