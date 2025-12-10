#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "SpriteLoader.h"

class Key : public BoxCollider {
	Texture* texture = new Texture();
	Sprite sprite;
	Animation idle;
	const float animationRate = 0.3f;
public:
	Key(b2World& world, b2Vec2 position);
	void Update(float deltaTime);
	void UpdateAnimation(float deltaTime);
	void Draw(RenderWindow& window);
	~Key() noexcept = default;
};