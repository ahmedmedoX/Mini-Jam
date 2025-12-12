#pragma once
#include "BoxCollider.h"

class GameObject {
protected:
	BoxCollider Collision_Box;
	RectangleShape Shape;
	RectangleShape collision;

public:
	GameObject(const b2Vec2 Position, b2World& world, const float width,
		const float height, const float friction, const bool isDynamic,
		ObjectType type);
	GameObject(const b2Vec2 Position, b2World& world, const float width,
		const float height, ObjectType type, int Level_Index);
	~GameObject();
	void Update();
	void Draw(RenderWindow& window);
	void setTexture(Texture* texture);
	b2Body* GetBody();
};