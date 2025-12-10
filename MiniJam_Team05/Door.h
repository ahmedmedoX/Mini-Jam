#pragma once
#include "BoxCollider.h"
#include "Animation.h"
#include "SpriteLoader.h"

class Door : public BoxCollider {
	Texture* texture = new Texture();
	Sprite sprite;
	const float animationRate = 0.3f;
public:
	Door(b2World& world, b2Vec2 position);
	void Update(float deltaTime);
	void Draw(RenderWindow& window);
	~Door() noexcept = default;
};