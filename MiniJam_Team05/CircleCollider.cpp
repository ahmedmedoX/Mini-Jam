//#include "CircleCollider.h"
//
//CircleCollider::CircleCollider(
//    b2Body* body,
//    float radius,
//    float density,
//    float friction,
//    b2World& world,
//    b2Vec2 Position
//)
//{
//    shape.m_radius = radius / 2.0f;
//    def.type = b2_dynamicBody;
//    def.position.Set(Position.x, Position.y);
//
//    body = world.CreateBody(&def);
//
//    fixtureDef.shape = &shape;
//    fixtureDef.density = density;
//    fixtureDef.friction = friction;
//    m_fixture = body->CreateFixture(&fixtureDef);
//}
