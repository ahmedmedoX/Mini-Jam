#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/box2d.h>

enum Direction
{
	LEFT,
	RIGHT,
	IDLE
};
enum Control
{
	INTERACT,
	NONE
};

class Player : public sf::Drawable ,  public b2ContactListener
{
private:
	b2Vec2 startPosition;
	b2World* world;

	b2Body* boxBody;

	sf::Texture* texture;
	sf::Sprite sprite;
	sf::RectangleShape rectangle;

	b2Filter filter;
	b2Filter groundFilter;
	b2Filter boxFilter;

	sf::Vector2f size;
	float density;
	float friction;
	float scale;
	bool interacting;

public :
	b2Body* body;
	float velocity;
	Player(b2World& world , float scale ,b2Vec2 position , b2Filter groundFilter , b2Filter boxFilter);
	void SetBody();
	void SetFillter();
	void SetFixture();	
	void SetSprite();
	void Update(Direction dir , Control control);
	void Move(Direction dir);
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};

