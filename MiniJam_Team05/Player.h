#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/box2d.h>
#include "Animation.h"

enum Direction
{
	LEFT = -1,
	RIGHT = 1,
	NOMOVE = 0
};
enum Control
{
	INTERACT,
	NONE
};
enum States
{
	MOVE,
	PUSH,
	PULL,
	FALL,
	DIE,
	IDLE,
};

class Player : public sf::Drawable ,  public b2ContactListener
{
private:
	b2Vec2 startPosition;
	b2World* world;

	b2Body* boxBody;

	sf::RectangleShape rectangle;

	b2Filter filter;
	b2Filter groundFilter;
	b2Filter boxFilter;

	sf::Texture* idleText;
	sf::Texture* runText;
	sf::Texture* pushText;
	sf::Texture* pullText;
	sf::Texture* fallText;	
	sf::Texture* dieText;

	Animation idle;
	Animation run;
	Animation push;
	Animation pull;
	Animation fall;
	Animation die;

	States currentState;
	sf::Sprite sprite;

	sf::Vector2f size;
	float density;
	float friction;
	float scale;
	bool interacting;
	float animationRate;

public :
	b2Body* body;
	float velocity;
	Player(b2World& world , float scale ,b2Vec2 position , b2Filter groundFilter , b2Filter boxFilter);
	void SetBody();
	void SetFillter();
	void SetFixture();	
	void InitializeAnimations();
	void Update(Direction dir , Control control , float deltaTime);
	void Move(Direction dir);
	void UpdateAnimation(float deltaTime ,Direction dir);
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~Player();
	
};

