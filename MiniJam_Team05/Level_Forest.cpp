#include "Level_Forest.h"

Level_Forest::Level_Forest(b2World& world) :
    Level(world,
        &SpriteLoader::getTexture(SpriteType::Level3),
        &SpriteLoader::getTexture(SpriteType::Level3_Background))
{
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(175, 77)),
        world, 128 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(340, 77)),
        world, 64 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 140)),
        world, 192 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(530, 84)),
        world, 192 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(656, 144)),
        world, 64 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(720, 240)),
        world, 64 / Utilities::PIXELS_PER_UNIT, 128 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(720, 532)),
        world, 64 / Utilities::PIXELS_PER_UNIT, 128 * 2.5f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(656, 720)),
        world, 64 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(456, 720)),
        world, 64 * 3 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(210, 720)),
        world, 64 * 3 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(80, 580)),
        world, 64  / Utilities::PIXELS_PER_UNIT, 64 * 3 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(144, 466)),
        world, 64  / Utilities::PIXELS_PER_UNIT, 64 * 3 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(84, 238)),
        world, 64  / Utilities::PIXELS_PER_UNIT, 64 * 4 / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    ///center of the level
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(290, 330)),
        world, 64 * 3  / Utilities::PIXELS_PER_UNIT, 64  / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(226, 266 )),
        world, 64   / Utilities::PIXELS_PER_UNIT, 64  / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(486, 272)),
        world, 64    / Utilities::PIXELS_PER_UNIT, 64 * 2  / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(518, 592)),
        world, 64 * 2    / Utilities::PIXELS_PER_UNIT, 64   / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(358, 490)),
        world, 62 * 2    / Utilities::PIXELS_PER_UNIT, 64   / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(599, 405)),
        world, 64     / Utilities::PIXELS_PER_UNIT, 64   / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    //spikes
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(332, 728)),0, 2));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(585, 728)),0, 2));

    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(600, 140)),180, 2));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(530, 140)),180, 2));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(270, 72)),180, 2));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(728, 336)),-90, 2));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(200, 405)),90, 2));
    //box
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(200, 200)),
        world, 64 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        BOX, 3));
    //key and door
    Level_Key = make_unique<Key>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(650, 650)));

    Level_Door = make_unique<Door>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(140, 650)));
}

Level_Forest::~Level_Forest() {}