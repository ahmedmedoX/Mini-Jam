#pragma once
#include "Utilities.h"

class Background {
	RectangleShape level;
	RectangleShape bg_Up;
	RectangleShape bg_Down;
	RectangleShape bg_Left;
	RectangleShape bg_Right;
public:
	Background(Texture* Level_Texture, Texture* Background_Texture);
	~Background();

	void Update(const float angle);
	void Draw(RenderWindow& window);
};