#include "Level_Rock.h"

Level_Rock::Level_Rock(b2World& world) :
	Level(world,
        &SpriteLoader::getTexture(SpriteType::Level1),
        &SpriteLoader::getTexture(SpriteType::Level1_Background))
{
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(384, 64 * 2.5f)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 128.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 600)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        BOX, 1));

    Level_Key = make_unique<Key>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(200, 200)));

    Level_Door = make_unique<Door>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 700)));

    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(450, 500)),90, 0));
}

Level_Rock::~Level_Rock() {}