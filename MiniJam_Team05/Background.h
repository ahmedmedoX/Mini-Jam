#pragma once
#include "Utilities.h"

class Background {
	RectangleShape Shape;
public:
	Background(std::shared_ptr<sf::Texture> bg);
	~Background();

	void Update(const float angle);
	void Draw(RenderWindow& window);
};