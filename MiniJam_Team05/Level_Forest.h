#pragma once
#include "Level.h"

class Level_Forest : public Level {
public:
	Level_Forest(b2World& world, std::shared_ptr<sf::Texture> bg);
	~Level_Forest();
};