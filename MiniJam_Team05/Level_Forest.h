#pragma once
#include "Level.h"

class Level_Forest : public Level {
public:
	Level_Forest(b2World& world, Texture* Background_Texture);
	~Level_Forest();
};