#include "Player.h"
#include <iostream>
#include "SpriteLoader.h"

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
	animationRate = 0.1f;

	filter.categoryBits = 0x0002;

	SetBody();
	SetFillter();
	SetFixture();
	InitializeAnimations();
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
void Player::InitializeAnimations()
{
	idleText = &SpriteLoader::getTexture(SpriteType::playerIdle);
	runText = &SpriteLoader::getTexture(SpriteType::playerRun);
	pushText = &SpriteLoader::getTexture(SpriteType::playerPush);
	pullText = &SpriteLoader::getTexture(SpriteType::playerPull);
	fallText = &SpriteLoader::getTexture(SpriteType::playerFall);
	dieText = &SpriteLoader::getTexture(SpriteType::playerDie);

	idle = Animation(idleText, sf::Vector2u(4,1), animationRate);
	run = Animation(runText, sf::Vector2u(7, 1), animationRate);
	push = Animation(pushText, sf::Vector2u(5, 1), animationRate);
	pull = Animation(pullText, sf::Vector2u(1, 1), animationRate);
	fall = Animation(fallText, sf::Vector2u(6, 1), animationRate);
	die = Animation(dieText, sf::Vector2u(6, 1), animationRate);

	sprite.setScale((size.x / idle.uvRect.width), (size.y / idle.uvRect.height));
}

void Player::Update(Direction dir , Control control, float deltaTime) {

	currentState = IDLE;
	if (control == Control::INTERACT && interacting && boxBody != nullptr){
		float dirX = static_cast<int>(dir);

			if (dir == Direction::NOMOVE) 
				return;

			float gravity = world->GetGravity().y;
			float pullForce = boxBody->GetMass() * gravity * 0.52f;  
			float playerDrag = body->GetMass() * gravity * 0.52f;  
			b2Vec2 direction = boxBody->GetPosition() - body->GetPosition();
			float dot = b2Dot(b2Vec2(direction.x , 0), b2Vec2(dirX, 0));

			if(dot > 0 ) 
				currentState = PUSH;
			else 
				currentState = PULL;

			boxBody->ApplyForceToCenter(b2Vec2(pullForce * dirX, 0), true);
			body->ApplyForceToCenter(b2Vec2(playerDrag * dirX, 0), true);
	}
	else if(dir != Direction::NOMOVE) {
		Move(dir);
		currentState = MOVE;
	}
	UpdateAnimation(deltaTime, dir);
}
void Player::Move(Direction dir)
{
	b2Vec2 vel = body->GetLinearVelocity();
	vel.x = velocity * static_cast<int>(dir);
	body->SetLinearVelocity(vel);
}

void Player::UpdateAnimation(float deltaTime , Direction dir) {
	Animation* animation = &idle;
	switch (currentState) {
		case IDLE:
			sprite.setTexture(*idleText);
			animation = &idle;
			break;
		case MOVE:
			sprite.setTexture(*runText);
			animation = &run;
			break;
		case PUSH:
			sprite.setTexture(*pushText);
			animation = &push;
			break;
		case PULL:
			sprite.setTexture(*pullText);
			animation = &pull;
			break;
		case FALL:
			sprite.setTexture(*fallText);
			animation = &fall;
			break;
		case DIE:
			sprite.setTexture(*dieText);
			animation = &die;
			break;
		default:
			break;
	}

	int dirVal = static_cast<int>(dir);
	if (currentState == PULL)
		dirVal *= -1;

	sprite.setOrigin(animation->uvRect.width / 2, animation->uvRect.height / 2);
	if(dir != Direction::NOMOVE)
		sprite.setScale(dirVal * (size.x / animation->uvRect.width), (size.y / animation->uvRect.height));

	animation->Update(0, deltaTime);
	sprite.setTextureRect(animation->uvRect);
	b2Vec2 pos = body->GetPosition();
	sprite.setPosition(pos.x * scale, pos.y * scale);
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
	target.draw(sprite, states);
};
Player::~Player() {
	world->DestroyBody(body);
}

