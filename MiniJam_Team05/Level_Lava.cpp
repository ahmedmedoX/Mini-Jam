#include "Level_Lava.h"

Level_Lava::Level_Lava(b2World& world) :
    Level(world,
        &SpriteLoader::getTexture(SpriteType::Level2),
        &SpriteLoader::getTexture(SpriteType::Level2_Background))
{
    Environment.clear();
    SetColliders(world);
    SetSpikes(world);
    SetDoor(world);
    SetKey(world);
    SetBox(world);
}

void Level_Lava::SetColliders(b2World& world) {
    sf::Vector2f leftPos_1(141.f, 143.f);
    sf::Vector2f leftPos_2(77.f, 400.f);
    sf::Vector2f leftPos_3(205.f, 497.f);
    sf::Vector2f leftPos_4(142.f, 657.f);

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(leftPos_1),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(leftPos_2),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 9 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(leftPos_3),
        world, 3 * 64.f / Utilities::PIXELS_PER_UNIT, 2 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(leftPos_4),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    sf::Vector2f bottomPos_1(237.f, 720.f);
    sf::Vector2f bottomPos_2(496.f, 690.f);
    sf::Vector2f bottomPos_3(650.f, 720.f);

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(bottomPos_1),
        world, 4 * 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(bottomPos_2),
        world, 2 * 64.f / Utilities::PIXELS_PER_UNIT, 2 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(bottomPos_3),
        world, 3 * 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    sf::Vector2f rightPos_1(720.f, 400.f);
    sf::Vector2f rightPos_2(658.f, 143.f);
    sf::Vector2f rightPos_3(658.f, 592.f);

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(rightPos_1),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 9 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(rightPos_2),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(rightPos_3),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    sf::Vector2f platform_1(574.f, 280.f);
    sf::Vector2f platform_2(438.f, 388.f);

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(platform_1),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(platform_2),
        world, 2 * 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    sf::Vector2f topPos_1(560.f, 83.f);
    sf::Vector2f topPos_2(430.f, 110.f);
    sf::Vector2f topPos_3(270.f, 175.f);
    sf::Vector2f topPos_4(206.f, 80.f);

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(topPos_1),
        world, 2 * 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(topPos_2),
        world, 2 * 64.f / Utilities::PIXELS_PER_UNIT, 2 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(topPos_3),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 4 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(topPos_4),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
}
void Level_Lava::SetSpikes(b2World& world) {
    sf::Vector2f spikePos_1(335.f, 70.f);
    sf::Vector2f spikePos_2(400.f, 730.f);
    sf::Vector2f spikePos_3(200.f, 652.f);
    sf::Vector2f spikePos_4(530.f, 140.f);
    sf::Vector2f spikePos_5(590.f, 140.f);
    sf::Vector2f spikePos_6(210.f, 135.f);
    sf::Vector2f spikePos_7(665.f, 652.f);

    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(spikePos_1), 180.f, 1));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(spikePos_2), 0.0f, 1));
    //Spikes.push_back(make_unique<Spike>(world,
    //    Utilities::Convert_SFML_Box2D_Space(spikePos_3), 90.f, 1));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(spikePos_4), 180.f, 1));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(spikePos_5), 180.f, 1));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(spikePos_6), 180.f, 1));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(spikePos_7), -90.f, 1));
}
void Level_Lava::SetDoor(b2World& world) {
    sf::Vector2f doorPos(445.f, 320.f);
    Level_Door = make_unique<Door>(world,
        Utilities::Convert_SFML_Box2D_Space(doorPos));
}
void Level_Lava::SetKey(b2World& world) {
    sf::Vector2f keyPos(200.f, 652.f);
    Level_Key = make_unique<Key>(world,
        Utilities::Convert_SFML_Box2D_Space(keyPos));
}
void Level_Lava::SetBox(b2World& world) {
    sf::Vector2f boxPos(200.f, 400.f);
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(boxPos),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        BOX, 2));
}
Level_Lava::~Level_Lava() {}