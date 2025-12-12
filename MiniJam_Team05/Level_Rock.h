#pragma once
#include "Level.h"

class Level_Rock : public Level {
public:
	Level_Rock(b2World& world);
	void SetColliders(b2World& world);
	void SetSpikes(b2World& world);
	void SetDoor(b2World& world);
	void SetKey(b2World& world);
	void SetBox(b2World& world);
	~Level_Rock();
};