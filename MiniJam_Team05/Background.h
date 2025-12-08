#pragma once
#include "Utilities.h"

class Background {
	RectangleShape Shape;
public:
	Background(Texture* Background_Texture);
	~Background();

	void Update(const float angle);
	void Draw(RenderWindow& window);
};