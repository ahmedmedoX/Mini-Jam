#include "BoxCollider.h"

using namespace std;

BoxCollider::BoxCollider(const float width,
    const float height, const float friction, b2World &world, const b2Vec2 Position,
    const bool dynamic, ObjectType type
)
{
    def.position = Position;
    def.type = dynamic ? b2_dynamicBody : b2_staticBody;

    body = world.CreateBody(&def);
    shape.SetAsBox((width / 2), (height / 2));
    fixtureDef.shape = &shape;

    fixtureDef.friction = dynamic ? 0.3f : friction;
    fixtureDef.density = dynamic ? 10.0f : 0.0f;
    fixtureDef.filter.categoryBits = type;
    fixtureDef.filter.maskBits = 0xFFFF;

    //body->SetBullet(true);
    body->SetAngularDamping(0.1);
    body->SetSleepingAllowed(false);
    body->CreateFixture(&fixtureDef);
}

BoxCollider::~BoxCollider(){
    if (body && body->GetWorld()) {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
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