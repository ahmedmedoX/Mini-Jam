#pragma once
#include "Level.h"

class Level_Lava : public Level {
public:
	Level_Lava(b2World& world);
	void SetColliders(b2World& world);
	void SetSpikes(b2World& world);
	void SetDoor(b2World& world);
	void SetKey(b2World& world);
	void SetBox(b2World& world);
	~Level_Lava();
};