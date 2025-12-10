#include "Level_Rock.h"

Level_Rock::Level_Rock(b2World& world, Texture* Background_Texture) :
	Level(world, Background_Texture)
{
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(384, 64 * 2.5f)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 128.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Level_Key = make_unique<Key>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(200, 200)));

    Level_Door = make_unique<Door>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(500, 700)));
}

Level_Rock::~Level_Rock() {}