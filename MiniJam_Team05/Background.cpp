#include "Background.h"

Background::Background(Texture* Level_Texture, Texture* Background_Texture) {
	level.setSize(Vector2f(704, 704));
	level.setOrigin(Vector2f(704 / 2, 704 / 2));
	level.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	level.setTexture(Level_Texture);

	Background_Texture->setRepeated(true);
	bg_Up.setSize(Vector2f(704*2, 704*2));
	bg_Up.setOrigin(Vector2f(704+32, (704 * 2)+32));
	bg_Up.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	bg_Up.setTextureRect(IntRect(0, 0, 704 , 704 ));
	bg_Up.setTexture(Background_Texture);

	bg_Down.setSize(Vector2f(704 * 2, 704 * 2));
	bg_Down.setOrigin(Vector2f(704 + 32, (704 * 2) + 32));
	bg_Down.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	bg_Down.setTextureRect(IntRect(0, 0, 704, 704));
	bg_Down.setTexture(Background_Texture);
	bg_Down.setRotation(180);

	bg_Left.setSize(Vector2f(704 * 2, 704 * 2));
	bg_Left.setOrigin(Vector2f(704 + 32, (704 * 2) + 32));
	bg_Left.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	bg_Left.setTextureRect(IntRect(0, 0, 704, 704));
	bg_Left.setTexture(Background_Texture);
	bg_Left.setRotation(-90);

	bg_Right.setSize(Vector2f(704 * 2, 704 * 2));
	bg_Right.setOrigin(Vector2f(704 + 32, (704 * 2) + 32));
	bg_Right.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2));
	bg_Right.setTextureRect(IntRect(0, 0, 704, 704));
	bg_Right.setTexture(Background_Texture);
	bg_Right.setRotation(90);
}

Background::~Background() {}

void Background::Update(const float angle) {
	level.setRotation(level.getRotation() - Utilities::Radian_to_Degree(angle));
	bg_Up.setRotation(level.getRotation());
	bg_Down.setRotation(level.getRotation() + 180);
	bg_Left.setRotation(level.getRotation() - 90);
	bg_Right.setRotation(level.getRotation() + 90);
}

void Background::Draw(RenderWindow& window) {
	window.draw(bg_Up);
	window.draw(bg_Down);
	window.draw(bg_Left);
	window.draw(bg_Right);
	window.draw(level);
}