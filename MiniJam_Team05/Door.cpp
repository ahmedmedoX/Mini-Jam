#include "Door.h"

Door::Door(b2World& world, b2Vec2 position)
    : BoxCollider(2.0f, 2.0f, 0.3f, world, position, false, DOOR)
{
    texture = &SpriteLoader::getTexture(SpriteType::doorSprite);
    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
}

void Door::Update(float deltaTime) {
    sprite.setPosition(Utilities::Convert_Box2D_SFML_Space(GetPosition()));
    sprite.setRotation(Utilities::Radian_to_Degree(GetAngle()));
}

void Door::Draw(RenderWindow& window) {
    window.draw(sprite);
}