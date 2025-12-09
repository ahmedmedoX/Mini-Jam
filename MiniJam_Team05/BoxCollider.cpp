#include "BoxCollider.h"
#include "Enums.h"

using namespace std;

BoxCollider::BoxCollider(const float width,
    const float height, const float friction, b2World &world, const b2Vec2 Position,
    const bool dynamic//, const unsigned int categoryBits 
)
{
    def.position.Set(Position.x, Position.y);
    def.type = dynamic ? b2_dynamicBody : b2_staticBody;

    body = world.CreateBody(&def);
    shape.SetAsBox((width / 2), (height / 2));
    fixtureDef.shape = &shape;

    //body->SetAngularDamping(0.1);
    fixtureDef.friction = friction;
    fixtureDef.density = dynamic ? 1.0f : 0.0f;
    fixtureDef.filter.categoryBits = 0x0001;
    fixtureDef.filter.maskBits =0xFFFF; 

    //body->SetBullet(true);
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
