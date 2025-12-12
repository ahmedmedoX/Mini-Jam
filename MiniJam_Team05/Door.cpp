#include "Door.h"

Door::Door(b2World& world, const b2Vec2 position)
    : BoxCollider(48 / Utilities::PIXELS_PER_UNIT, 64 / Utilities::PIXELS_PER_UNIT,
        1.0f, world, position, false, DOOR)
{
    texture = &SpriteLoader::getTexture(SpriteType::doorSprite);
    sprite.setTexture(*texture);
    sprite.setScale(1.5f, 1.5f);
    sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
    collision.setSize(Vector2f(48, 64));
    collision.setFillColor(Color(0, 255, 0, 120));
    collision.setOrigin(Vector2f(48/2, 64/2));
}

void Door::Update() {
    sprite.setPosition(Utilities::Convert_Box2D_SFML_Space(GetPosition()));
    sprite.setRotation(Utilities::Radian_to_Degree(-GetAngle()));
    collision.setPosition(Utilities::Convert_Box2D_SFML_Space(GetPosition()));
    collision.setRotation(Utilities::Radian_to_Degree(-GetAngle()));
}

void Door::Draw(RenderWindow& window) {
    window.draw(sprite);
    if (Utilities::DEBUG)
        window.draw(collision);
}