#pragma once

#include <Box2D/box2d.h>
#include "Animation.h"
#include "SpriteLoader.h"
#include "Enums.h"
#include "Utilities.h"

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

class Player : public Drawable, public b2ContactListener {
private:
	b2World* world;
	b2Body* boxBody;

	b2Fixture* footSensor;

	b2Filter filter;

	std::map<States, Animation> animations;
	std::map<States, Texture*> textures;

	States currentState;
	Sprite sprite;

	const Vector2f size = Vector2f(32.f, 48.f);
	const float walkVelocity = 80.0f / Utilities::PIXELS_PER_UNIT;
	const float fallVelocity = 5.0f / Utilities::PIXELS_PER_UNIT;
	bool interacting;
	float animationRate;
	int footContacts = 0;
	bool onGround = false;
	int collectables = 0;

public:
	b2Body* body;
	float velocity;
	Player(b2World& world, const b2Vec2 position);
	void SetBody(const b2Vec2 Position);
	void SetFixture();
	void InitializeAnimations();
	void Update(Direction dir, Control control, float deltaTime);
	void Move(Direction dir);
	void UpdateAnimation(const float deltaTime, Direction dir);
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	int GetCollectablesNumber();
	void draw(RenderTarget& target, RenderStates states) const override;
	~Player();
};