#include "Background.h"

Background::Background(std::shared_ptr<sf::Texture> bg) {
	Shape.setSize(Vector2f(bg->getSize().x, bg->getSize().y));
	Shape.setOrigin(Vector2f(bg->getSize().x / 2, bg->getSize().y / 2));
	Shape.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	Shape.setTexture(bg.get());
	if (true) {
		Shape.setFillColor(Color(255, 255, 255, 126));
	}
}

Background::~Background() {}

void Background::Update(const float angle) {
	Shape.setRotation(Shape.getRotation() - Utilities::Radian_to_Degree(angle));
}

void Background::Draw(RenderWindow& window) {
	window.draw(Shape);
}