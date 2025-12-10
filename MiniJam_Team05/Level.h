#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Platform.h"


class Level : public sf::Drawable
{

private:

	sf::Texture* backgroundTexture;
	sf::Sprite* backgroundSprite;

	std::vector<Platform> platforms;

public:
	Level(b2World& world, float scale);
	void SetWalls(b2World& world, float scale );
	void SetPlatforms(b2World& world, float scale );
	void Update();	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;	
	~Level();
};

