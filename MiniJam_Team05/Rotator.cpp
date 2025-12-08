#include "Rotator.h"

void Rotator::RotateLevel(vector<GameObject*>& objects, b2World& world,
    const b2Vec2& center, const float angle)
{
    for (int i = 0; i < objects.size(); i++)
	{
		rotateBodyAround(objects[i]->GetBody(), center, angle);
	}
}

void Rotator:: rotateBodyAround(b2Body* body, const b2Vec2& center, const float angle) {
    const float c = cos(angle);
    const float s = sin(angle);

    b2Vec2 p = body->GetPosition();

    const float xr = ((p.x - center.x) * c) - ((p.y - center.y) * s);
    const float yr = ((p.x - center.x) * s) + ((p.y - center.y) * c);

    body->SetTransform({ center.x + xr, center.y + yr }, body->GetAngle() + angle);
}