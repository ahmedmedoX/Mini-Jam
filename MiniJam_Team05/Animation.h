#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Animation {
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
public:
	IntRect uvRect;
	Animation();
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	void Update(int row, float deltaTime);
};