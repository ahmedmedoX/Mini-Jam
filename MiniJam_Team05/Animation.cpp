#include "Animation.h"

Animation::Animation() {}

Animation::Animation(sf::Texture* texture , const sf::Vector2u imageCount, const float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	currentImage.x = 0;
	currentImage.y = 0;
	totalTime = 0.f;
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(const int row, const float deltaTime) {
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::Update(const float deltaTime) {
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
			currentImage.y++;
			if (currentImage.y >= imageCount.y) {
				currentImage.x = 0;
				currentImage.y = 0;
			}
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

Animation::~Animation(){}