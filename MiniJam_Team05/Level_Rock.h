#pragma once
#include "Level.h"

class Level_Rock : public Level {
public:
	Level_Rock(b2World& world, Texture* Background_Texture);
	~Level_Rock();
};