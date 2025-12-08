#include "Background.h"

Background::Background(Texture* Background_Texture) {
	Shape.setSize(Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
	Shape.setOrigin(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	Shape.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	Shape.setTexture(Background_Texture);
}

Background::~Background() {}

void Background::Update(const float angle) {
	Shape.setRotation(Shape.getRotation() - Utilities::Radian_to_Degree(angle));
}

void Background::Draw(RenderWindow& window) {
	window.draw(Shape);
}