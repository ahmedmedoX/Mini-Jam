#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
class Cell : public sf::Drawable , public sf::Transformable
{
private:

	sf::Texture* texture;
	sf::Sprite sprite;
	b2Vec2 position;
	float rotation;
	sf::Vector2f cellSize;
	
public:
	Cell( sf::Vector2f size ,b2Vec2 position);
	void SetTexture();
	void Update();
	void SetPosition(b2Vec2 pos);
	void setRotation(float angle);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~Cell();
};

