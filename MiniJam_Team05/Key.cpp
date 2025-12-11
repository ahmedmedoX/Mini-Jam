#include "Key.h"

Key::Key(b2World& world, const b2Vec2 position)
    : BoxCollider(32 / Utilities::PIXELS_PER_UNIT, 32 / Utilities::PIXELS_PER_UNIT,
        0.3f, world, position, false, KEY)
{
    texture = &SpriteLoader::getTexture(SpriteType::keyIdle);
    Sparkle_texture = &SpriteLoader::getTexture(SpriteType::sparkleSprite);

    idle = Animation(texture, { 5, 1 }, animationRate);
    Sparkle_Anim = Animation(Sparkle_texture, { 4, 4 }, animationRate * 0.8f);

    sprite.setTexture(*texture);
    sprite.setScale(32.0f / idle.uvRect.width, 32.0f / idle.uvRect.height);
    sprite.setOrigin(idle.uvRect.width / 2.0f, idle.uvRect.height / 2.0f);

    Sparkle.setTexture(*Sparkle_texture);
    Sparkle.setScale(40.0f / Sparkle_Anim.uvRect.width, 40.0f / Sparkle_Anim.uvRect.height);
    Sparkle.setOrigin(Sparkle_Anim.uvRect.width / 2.0f, Sparkle_Anim.uvRect.height / 2.0f);
}

void Key::Update(const float deltaTime) {
    UpdateAnimation(deltaTime);
    sprite.setPosition(Utilities::Convert_Box2D_SFML_Space(GetPosition()));
    Sparkle.setPosition(sprite.getPosition());
}

void Key::UpdateAnimation(const float deltaTime) {
    idle.Update(0, deltaTime);
    sprite.setScale(32.0f / idle.uvRect.width, 32.0f / idle.uvRect.height);
    //sprite.setOrigin(idle.uvRect.width / 2.0f, idle.uvRect.height / 2.0f);
    sprite.setTextureRect(idle.uvRect);

    Sparkle_Anim.Update(deltaTime);
    Sparkle.setScale(40.0f / Sparkle_Anim.uvRect.width, 40.0f / Sparkle_Anim.uvRect.height);
    //Sparkle.setOrigin(Sparkle_Anim.uvRect.width / 2.0f, Sparkle_Anim.uvRect.height / 2.0f);
    Sparkle.setTextureRect(Sparkle_Anim.uvRect);
}

void Key::Draw(RenderWindow& window) {
    window.draw(Sparkle);
    window.draw(sprite);
}