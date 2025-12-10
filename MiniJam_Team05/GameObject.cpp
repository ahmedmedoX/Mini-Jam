#include "GameObject.h"

GameObject::GameObject(const b2Vec2 Position, b2World& world, const float width,
    const float height, const float friction, const bool isDynamic, ObjectType type)
    : Collision_Box(width, height, friction, world, Position, isDynamic, type)
{
    Shape.setSize(Vector2f(width * Utilities::PIXELS_PER_UNIT, height * Utilities::PIXELS_PER_UNIT));
    Shape.setOrigin(Vector2f(width * Utilities::PIXELS_PER_UNIT / 2.0f, height * Utilities::PIXELS_PER_UNIT / 2.0f));
    Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Position));
    Shape.setFillColor(Color(255, 255, 255, 128));
}

GameObject::~GameObject(){}

void GameObject::Update() {
    Shape.setRotation(Collision_Box.GetAngle() * -180.f / 3.14f);
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