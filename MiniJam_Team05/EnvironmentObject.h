#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/box2d.h>
#include "Animation.h"
#include "Enums.h"

class EnvironmentObject : public sf::Drawable	
{
private:
	b2Vec2 startPosition;
	b2World* world;

	b2Filter filter;

	sf::Texture* texture;
	sf::Sprite sprite;
	Animation idle;

	sf::Vector2f size;

	float density;
	float friction;
	float scale;
	float animationRate;
	float boxDensity;

public:
	b2Body* body;
	EnvironmentObject(b2World& world, float scale, b2Vec2 position ,ObjectType type );
	void SetBody();
	void SetFixture();
	void InitializeAnimations();
	void Update(float deltaTime);
	void UpdateAnimation(float deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~EnvironmentObject();
};

