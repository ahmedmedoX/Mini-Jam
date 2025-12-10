#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Platform : public sf::Drawable
{
private:

	b2Vec2 position;
	int length;
	float scale;
	sf::Vector2f cellSize;
	b2Body* body;
	b2Filter filter;
	std::vector<Cell> cells;
public:

	Platform(b2World& world , float scale , int length ,sf::Vector2f cellSize, b2Vec2 position);
	void SetBody(b2World& world);
	void SetFixture();
	void SetCells();
	void Update();
	void setRotation(float angle);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~Platform();
};

