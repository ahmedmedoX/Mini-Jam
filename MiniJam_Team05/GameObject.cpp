#include "GameObject.h"

GameObject::GameObject(const b2Vec2 Position, b2World& world, const float width,
    const float height, const float friction, const bool isDynamic)
    : Collision_Box(width, height, friction, world, Position, isDynamic)
{
    Shape.setSize(Vector2f(width * Utilities::PIXELS_PER_UNIT, height * Utilities::PIXELS_PER_UNIT));
    Shape.setOrigin(Vector2f(width * Utilities::PIXELS_PER_UNIT / 2.0f, height * Utilities::PIXELS_PER_UNIT / 2.0f));
    Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Position));
}

GameObject::~GameObject(){
    Collision_Box.~BoxCollider();
}

void GameObject::Update() {
    float angle = Collision_Box.GetAngle();
    Shape.setRotation(angle * -180.f / 3.14f);
    Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Collision_Box.GetPosition()));
}

void GameObject::Draw(RenderWindow& window) {
    window.draw(Shape);
}
void GameObject::setFillColor(const Color& color) {
    Shape.setFillColor(color);
}

void GameObject::setTexture(Texture* texture) {
    Shape.setTexture(texture);
}

b2Body* GameObject::GetBody() {
    return Collision_Box.GetBody();
}