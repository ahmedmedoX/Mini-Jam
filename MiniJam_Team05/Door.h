#pragma once
#include "BoxCollider.h"
#include "Animation.h"
#include "SpriteLoader.h"

class Door : public BoxCollider {
	Texture* texture = new Texture();
	Sprite sprite;
public:
	Door(b2World& world, const b2Vec2 position);
	void Update();
	void Draw(RenderWindow& window);
	~Door() noexcept = default;
};