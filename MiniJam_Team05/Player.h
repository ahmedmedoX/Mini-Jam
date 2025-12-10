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
	IDLE,
};

class Player : public sf::Drawable ,  public b2ContactListener
{
private:
	b2Vec2 startPosition;
	b2Body* boxBody;
	b2Fixture* footSensor;
	b2Filter filter;

	std::map<States, Animation> animations;
	std::map<States, sf::Texture*> textures;

	States currentState;
	sf::Sprite sprite;

	sf::Vector2f size;
	float walkVelocity;
	float fallVelocity;
	float density;
	float friction;
	float scale;
	bool interacting;
	float animationRate;
	int footContacts = 0;
	bool onGround = false;

	int collectables = 0;

public :
	b2Body* body;
	float velocity;
	Player(b2World& world, float scale, b2Vec2 position);
	void SetBody(b2World& world);
	void SetFixture();	
	void InitializeAnimations();
	void Update(b2World& world, Direction dir , Control control , float deltaTime);
	void Move(Direction dir);
	void UpdateAnimation(float deltaTime ,Direction dir);
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	int GetCollectablesNumber();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~Player();
	
};

