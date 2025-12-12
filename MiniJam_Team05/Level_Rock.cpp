#include "Level_Rock.h"

Level_Rock::Level_Rock(b2World& world)
    :Level(world,
        &SpriteLoader::getTexture(SpriteType::Level1),
        &SpriteLoader::getTexture(SpriteType::Level1_Background))
{
	Environment.clear();
	SetColliders(world);
	SetSpikes(world);
	SetDoor(world);
	SetKey(world);
	SetBox(world);
}

void Level_Rock::SetColliders(b2World& world) {

	sf::Vector2f pos1(627, 368);
    sf::Vector2f pos2(625, 655);
    sf::Vector2f pos3(305, 385);
    sf::Vector2f pos4(207, 240);
    sf::Vector2f pos5(80, 590);
    sf::Vector2f pos6(280, 720);
    sf::Vector2f pos7(720, 370);
    sf::Vector2f pos8(80, 270);
    sf::Vector2f pos9(270, 110);
    sf::Vector2f pos10(470, 110);
    sf::Vector2f pos11(595, 80);
    sf::Vector2f pos12(200, 590);
    sf::Vector2f pos13(528, 528);
    sf::Vector2f pos14(528,720);
    sf::Vector2f pos15(145, 200-60);

    Environment.push_back(make_unique<GameObject>(
    Utilities::Convert_SFML_Box2D_Space(pos1),
    world,  2*64.f / Utilities::PIXELS_PER_UNIT, 2*64.f / Utilities::PIXELS_PER_UNIT,
    2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos2),
        world, 2 * 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos3),
        world, 2 * 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos4),
        world, 64.f / Utilities::PIXELS_PER_UNIT,2* 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos5),
        world,  64.f / Utilities::PIXELS_PER_UNIT, 3*64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos6),
        world, 5*64.f / Utilities::PIXELS_PER_UNIT,  64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos7),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 8 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos8),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 5 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos9),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 2 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos10),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 2 * 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos11),
        world, 3 * 64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos12),
        world,  64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos13),
        world,  64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos14),
        world,  64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(pos15),
        world,  64.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));
}
void Level_Rock::SetSpikes(b2World& world) {

    Spikes.push_back(make_unique<Spike>(world,
		Utilities::Convert_SFML_Box2D_Space(Vector2f(465, 730)), 0, 0));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(70, 460)), 90, 0));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(340, 70)), 180, 0));
    Spikes.push_back(make_unique<Spike>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(410, 70)), 180, 0));
}

void Level_Rock::SetDoor(b2World& world) {
    Level_Door = make_unique<Door>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(140, 350)));
}

void Level_Rock::SetKey(b2World& world) {
    Level_Key = make_unique<Key>(world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(300, 650)));
}

void Level_Rock::SetBox(b2World& world) {
    Environment.push_back(make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(630, 270)),
        world, 60.f / Utilities::PIXELS_PER_UNIT, 60.f / Utilities::PIXELS_PER_UNIT,
        BOX, 1));
}

Level_Rock::~Level_Rock() {}