#pragma once
#include "Level.h"

class Level_Rock : public Level {
public:
	Level_Rock(b2World& world, std::shared_ptr<sf::Texture> bg);
	~Level_Rock();
};