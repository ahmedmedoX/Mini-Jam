#pragma once
#include "Level.h"

class Level_Lava : public Level {
public:
	Level_Lava(b2World& world);
	void SetWalls(b2World& world);
	void SetSpikes(b2World& world);
	~Level_Lava();
};