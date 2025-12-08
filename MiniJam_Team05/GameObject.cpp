#include "GameObject.h"

GameObject::GameObject(const b2Vec2 Position, b2World& world, Texture* texture,
	const float width, const float height, const float friction)
    : Collision_Box(width,
                    height,
                    friction,
                    world,
                    Position,
                    false)
{
    Shape.setSize(Vector2f(width * Utilities::PIXELS_PER_UNIT, height * Utilities::PIXELS_PER_UNIT));
    Shape.setOrigin(Vector2f(width * Utilities::PIXELS_PER_UNIT / 2.0f, height * Utilities::PIXELS_PER_UNIT / 2.0f));
    Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Position));
    Shape.setTexture(texture);
}

GameObject::~GameObject(){
    Collision_Box.~BoxCollider();
}

void GameObject::Update() {
    b2Vec2 pos = Collision_Box.GetPosition();
    float angle = Collision_Box.GetAngle();
    Shape.setRotation(angle * 180.f / 3.14159f);
    Shape.setPosition(pos.x * Utilities::PIXELS_PER_UNIT, pos.y * Utilities::PIXELS_PER_UNIT);
    //Shape.setPosition(Utilities::Convert_Box2D_SFML_Space(Collision_Box.GetPosition()));
}

void GameObject::Draw(RenderWindow& window) {
    window.draw(Shape);
}
void GameObject::setFillColor(const Color& color)
{
    Shape.setFillColor(color);
}

b2Body* GameObject::GetBody() {
    return Collision_Box.GetBody();
}