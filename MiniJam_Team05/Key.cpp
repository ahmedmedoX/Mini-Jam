#include "Key.h"
Key::Key(b2World& world, b2Vec2 position)
    : BoxCollider(2.0f, 2.0f, 0.3f, world, position, false, KEY)
{
    texture = &SpriteLoader::getTexture(SpriteType::keyIdle);
    idle = Animation(texture, { 5, 1 }, animationRate);
    sprite.setTexture(*texture);
    sprite.setScale(32.0f / idle.uvRect.width, 32.0f / idle.uvRect.height);
    sprite.setOrigin(idle.uvRect.width / 2.0f, idle.uvRect.height / 2.0f);
    //sprite.setPosition(Utilities::Convert_Box2D_SFML_Space(GetPosition()));
}

Key::~Key() {}

void Key::Update(float deltaTime) {
    UpdateAnimation(deltaTime);
    sprite.setPosition(Utilities::Convert_Box2D_SFML_Space(GetPosition()));
}

void Key::UpdateAnimation(float deltaTime) {
    idle.Update(0, deltaTime);
    sprite.setScale(32.0f / idle.uvRect.width, 32.0f / idle.uvRect.height);
    sprite.setOrigin(idle.uvRect.width / 2.0f, idle.uvRect.height / 2.0f);
    sprite.setTextureRect(idle.uvRect);
}

void Key::Draw(RenderWindow& window) {
    window.draw(sprite);
}