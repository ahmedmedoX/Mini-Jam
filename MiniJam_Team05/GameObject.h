#pragma once
#include "BoxCollider.h"

class GameObject {
	BoxCollider Collision_Box;
	RectangleShape Shape;
public:
	GameObject(const b2Vec2 Position, b2World& world, const float width,
		const float height, const float friction, const bool isDynamic);
	~GameObject();
	void Update();
	void Draw(RenderWindow& window);
	void setFillColor(const Color& color);
	void setTexture(Texture* texture);
	b2Body* GetBody();
};