#pragma once
#include "BoxCollider.h"

class GameObject
{
	BoxCollider Collision_Box;
	RectangleShape Shape;
public:
	GameObject(const b2Vec2 Position, b2World& world, Texture* texture,
		const float width, const float height, const float friction);
	~GameObject();
	void Update();
	void Draw(RenderWindow& window);
	void setFillColor(const Color& color);
	b2Body* GetBody();
};