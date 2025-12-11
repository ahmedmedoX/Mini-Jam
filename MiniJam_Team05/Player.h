#pragma once

#include "Animation.h"
#include "SpriteLoader.h"
#include "Enums.h"
#include "Utilities.h"

enum Direction {
	LEFT = -1,
	RIGHT = 1,
	NOMOVE = 0
};

enum Control {
	INTERACT,
	NONE
};

enum States {
	MOVE,
	PUSH,
	PULL,
	FALL,
	IDLE,
};

class Player : public Drawable, public b2ContactListener {
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
	const float fallVelocity = 80.0f / Utilities::PIXELS_PER_UNIT;
	const float animationRate = 0.4f;

	bool interacting;
	int footContacts = 0;
	bool onGround = false;
	bool is_Key_Collected = false;
	bool is_Door_Opened = false;
	bool is_Player_Lost = false;

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
	bool isKeyCollected();
	bool isPlayerLost();
	bool isDoorOpened();
	void draw(RenderTarget& target, RenderStates states) const override;
	~Player();
};