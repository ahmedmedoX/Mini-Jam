#include "BoxCollider.h"

using namespace std;

BoxCollider::BoxCollider(const float width,
    const float height, const float friction, b2World &world, const b2Vec2 Position,
    const bool dynamic//, const unsigned int categoryBits 
)
{
    def.position.Set(Position.x, Position.y);
    def.type = dynamic ? b2_dynamicBody : b2_staticBody;

    body = world.CreateBody(&def);
    shape.SetAsBox(width / 2.0f, height / 2.0f, Position, 0.0f);

    fixtureDef.shape = &shape;
    fixtureDef.friction = friction;
    fixtureDef.density = dynamic ? 1.0f : 0.0f;
    //fixtureDef.filter.categoryBits = 0x0001;

    body->CreateFixture(&fixtureDef);
    body->SetSleepingAllowed(false);
}

BoxCollider::~BoxCollider(){
    if (body && body->GetWorld())
        body->GetWorld()->DestroyBody(body);
}

b2Vec2 BoxCollider::GetPosition() {
    return body->GetPosition();
}

float BoxCollider::GetAngle() {
    return body->GetAngle();
}

b2Body* BoxCollider::GetBody() {
    return body;
}