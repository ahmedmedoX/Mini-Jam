#include "Spike.h"

Spike::Spike(b2World& world, const b2Vec2 position, const int Level_Index)
    : BoxCollider(32 / Utilities::PIXELS_PER_UNIT, 32 / Utilities::PIXELS_PER_UNIT,
        0.3f, world, position, false, SPIKE)
{
    switch (Level_Index) {
        case (0): {
            texture = &SpriteLoader::getTexture(SpriteType::spike1Sprite);
            break;
        }
        case (1): {
            texture = &SpriteLoader::getTexture(SpriteType::spike2Sprite);
            break;
        }
        case (2): {
            texture = &SpriteLoader::getTexture(SpriteType::spike3Sprite);
            break;
        }
        default:
            texture = &SpriteLoader::getTexture(SpriteType::spike1Sprite);
    }

    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
}

void Spike::Update() {
    sprite.setPosition(Utilities::Convert_Box2D_SFML_Space(GetPosition()));
    sprite.setRotation(Utilities::Radian_to_Degree(-GetAngle()));
}

void Spike::Draw(RenderWindow& window) {
    window.draw(sprite);
}