#include "Player.h"
#include <iostream>

Player::Player(b2World& world , float scale , b2Vec2 position, b2Filter groundFilter, b2Filter boxFilter)
{
	this->world = &world;
	this->scale = scale;
	this->startPosition = position;
	interacting = false;
	this->groundFilter = groundFilter;
	this->boxFilter = boxFilter;

	size = sf::Vector2f(50.0f, 50.0f);
	density = 1.0f;
	friction = 0.3f;
	velocity = 10.0f / scale;

	SetBody();
	SetFillter();
	SetFixture();
	SetSprite();
}

void Player::SetBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(startPosition.x/scale, startPosition.y/scale);
	body = world->CreateBody(&bodyDef);
}
void Player::SetFillter()
{
	filter.categoryBits = 0x0002;
	filter.maskBits = 0xFFFF & (groundFilter.categoryBits | boxFilter.categoryBits);
}
void Player::SetFixture()
{
	b2PolygonShape boxShape;
	boxShape.SetAsBox((size.x/2) /scale, (size.y/2) / scale );
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = density ;
	fixtureDef.friction = friction;
	fixtureDef.filter = filter;
	body->CreateFixture(&fixtureDef);
}	

void Player::SetSprite()
{
	rectangle.setSize(size);
	rectangle.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f pos = sf::Vector2f(startPosition.x, startPosition.y);
	rectangle.setPosition(pos);
	rectangle.setFillColor(sf::Color::Magenta);
}

void Player::Move(Direction dir)
{
	b2Vec2 vel = body->GetLinearVelocity();

	switch (dir) {
	case LEFT:
		vel.x = -velocity;
		break;
	case RIGHT:
		vel.x = velocity;
		break;
	case IDLE:
		vel.x = 0.0f;
		break;
	}

	body->SetLinearVelocity(vel);
}
void Player::Update(Direction dir , Control control) {

	Move(dir);
	b2Vec2 pos = body->GetPosition();
	rectangle.setPosition(pos.x * scale, pos.y * scale);
}

void Player::BeginContact(b2Contact* contact)
{
	b2Filter filterA = contact->GetFixtureA()->GetFilterData();
	
	if (filterA.categoryBits == boxFilter.categoryBits)
	{
		boxBody = contact->GetFixtureA()->GetBody();
		interacting = true;
		std::cout << "Begin Contact with Box A\n";
	}
}
void Player::EndContact(b2Contact* contact) {
	b2Filter filterA = contact->GetFixtureA()->GetFilterData();
	
	if (filterA.categoryBits == boxFilter.categoryBits)
	{
		boxBody = nullptr;
		interacting = false;
		std::cout << "End Contact with Box\n";
	}
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rectangle, states);
};

