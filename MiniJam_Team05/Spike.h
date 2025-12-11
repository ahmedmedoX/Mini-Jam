#pragma once
#include "BoxCollider.h"
#include "SpriteLoader.h"

class Spike : public BoxCollider {
	Texture* texture = new Texture();
	Sprite sprite;
public:
	Spike(b2World& world, const b2Vec2 position, const int Level_Index);
	void Update();
	void Draw(RenderWindow& window);
	~Spike() noexcept = default;
};