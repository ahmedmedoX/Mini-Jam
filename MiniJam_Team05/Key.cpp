#include "Key.h"
Key::Key(b2World& world, b2Vec2 position)
    : GameObject(position, world, 1.0f, 1.0f, 1.0f, false, KEY)
{
    texture = &SpriteLoader::getTexture(SpriteType::keyIdle);
    idle = Animation(texture, { 5, 1 }, animationRate);
    sprite.setTexture(*texture);
    sprite.setScale(32.0f / idle.uvRect.width, 32.0f / idle.uvRect.height);
    sprite.setOrigin(idle.uvRect.width / 2.0f, idle.uvRect.height / 2.0f);
}

Key::~Key() {}

void Key::Update(float deltaTime) {
    sprite.setPosition(Utilities::Convert_Box2D_SFML_Space(Collision_Box.GetPosition()));
}

void Key::UpdateAnimation(float deltaTime) {
    idle.Update(0, deltaTime);
    sprite.setScale(32.0f / idle.uvRect.width, 32.0f / idle.uvRect.height);
    sprite.setOrigin(idle.uvRect.width / 2.0f, idle.uvRect.height / 2.0f);
    sprite.setTextureRect(idle.uvRect);
}

void Key::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}