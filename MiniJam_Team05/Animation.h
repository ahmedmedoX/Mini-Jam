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
	Animation(sf::Texture* texture, const sf::Vector2u imageCount, const float switchTime);
	~Animation();
	void Update(const int row, const float deltaTime);
	void Update(const float deltaTime);
};