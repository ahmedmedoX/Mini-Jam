#pragma once
#include "Utilities.h"
#include "Enums.h"

class BoxCollider {
    b2BodyDef def;
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;
    b2Body* body = nullptr;
public:
    BoxCollider(const float width, const float height, const float friction,
        b2World& world, const b2Vec2 Position, const bool dynamic,
        ObjectType type);
    ~BoxCollider();
    b2Vec2 GetPosition();
    float GetAngle();
    b2Body* GetBody();
};