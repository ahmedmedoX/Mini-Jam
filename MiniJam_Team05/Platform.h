#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Platform
{
private:
	b2World& world;
	float scale;
	float length;
	b2Vec2 position;
	b2Vec2 rotation;
	b2Body* body;
	sf::Texture* texture;
	sf::Sprite sprite;
public:

	Platform(b2World& world , float scale , float length , b2Vec2 position , b2Vec2 rotation);
	void SetBody();
	void SetFixture();
	void SetTexture();
	~Platform();
};

