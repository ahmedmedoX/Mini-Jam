#include "GameObject.h"
#include "SpriteLoader.h"
#include "FilePathes.h"

GameObject::GameObject(const b2Vec2 Position, b2World& world, const float width,
    const float height, const float friction, const bool isDynamic, ObjectType type)
    : Collision_Box(width, height, friction, world, Position, isDynamic, type)
{
    Shape.setSize(Vector2f(width * Utilities::PIXELS_PER_UNIT, height * Utilities::PIXELS_PER_UNIT));
    Shape.setOrigin(Vector2f(width * Utilities::PIXELS_PER_UNIT / 2.0f, height * Utilities::PIXELS_PER_UNIT / 2.0f));
    Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Position));
    Shape.setFillColor(Color(255, 255, 255, 128));
}

GameObject::GameObject(const b2Vec2 Position, b2World& world, const float width,
    const float height, ObjectType type, int Level_Index)
    : Collision_Box(width, height, 2.0f, world, Position, true, type)
{
    switch (Level_Index)
    {
    case(1): {
        Shape.setTexture(&SpriteLoader::getTexture(SpriteType::box1Sprite));
        break;
    }
    case(2): {
        Shape.setTexture(&SpriteLoader::getTexture(SpriteType::box2Sprite));
        break;
    }
    case(3): {
        Shape.setTexture(&SpriteLoader::getTexture(SpriteType::box3Sprite));
        break;
    }
    default:
        break;
    }

    Shape.setSize(Vector2f(width * Utilities::PIXELS_PER_UNIT, height * Utilities::PIXELS_PER_UNIT));
    Shape.setOrigin(Vector2f(width * Utilities::PIXELS_PER_UNIT / 2.0f, height * Utilities::PIXELS_PER_UNIT / 2.0f));
    Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Position));
    //Shape.setFillColor(Color(255, 255, 255, 128));
}

GameObject::~GameObject(){}

void GameObject::Update() {
    Shape.setRotation(Utilities::Radian_to_Degree(-Collision_Box.GetAngle()));
    Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Collision_Box.GetPosition()));
}

void GameObject::Draw(RenderWindow& window) {
    window.draw(Shape);
}

void GameObject::setTexture(Texture* texture) {
    Shape.setTexture(texture);
}

b2Body* GameObject::GetBody() {
    return Collision_Box.GetBody();
}