#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "SpriteLoader.h"

class Key : public GameObject, public Drawable {
	Texture* texture = new Texture();
	Sprite sprite;
	Animation idle;
	float animationRate = 1.0f;
public:
	Key(b2World& world, b2Vec2 position);
	void Update(float deltaTime);
	void UpdateAnimation(float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~Key();
};