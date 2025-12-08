#include "Rotator.h"

void Rotator::RotatLevel(std::vector<GameObject*>& objects, b2World& world, b2Vec2& center, float angleRad)
{
    for (int i = 0; i < objects.size(); i++)
	{
		rotateBodyAround(objects[i]->GetBody(), center, angleRad);
	}
}

void Rotator:: rotateBodyAround(b2Body* body, const b2Vec2& center, float angleRad)
{
    float c = cos(angleRad);
    float s = sin(angleRad);

    b2Vec2 p = body->GetPosition();

    float x = p.x - center.x;
    float y = p.y - center.y;

    float xr = x * c - y * s;
    float yr = x * s + y * c;

    body->SetTransform({ center.x + xr, center.y + yr },
        body->GetAngle() + angleRad);
}




