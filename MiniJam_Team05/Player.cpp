#include "Player.h"
#include <iostream>
#include "SpriteLoader.h"
#include "Enums.h"  

Player::Player(b2World& world, float scale, b2Vec2 position)
{
    this->scale = scale;
    this->startPosition = position;

    interacting = false;
    boxBody = nullptr;

    size = sf::Vector2f(32.f, 48.f);
    density = 1.0f;
    friction = 0.3f;
    walkVelocity = 50.0f / scale;
	fallVelocity = 5.0f / scale;
	velocity = walkVelocity;
    animationRate = 0.1f;

    footContacts = 0;
    onGround = false;

    filter.categoryBits = PLAYER;
    filter.maskBits = GROUND | BOX | KEY | SPIKE | DOOR;

    SetBody(world);
    SetFixture();
    InitializeAnimations();
}

void Player::SetBody(b2World& world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(startPosition.x / scale, startPosition.y / scale);
    //bodyDef.fixedRotation = true;
    body = world.CreateBody(&bodyDef);
}

void Player::SetFixture()
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox((size.x / 2) / scale, (size.y / 2) / scale);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.filter = filter;

    body->CreateFixture(&fixtureDef);

    b2PolygonShape footShape;
    footShape.SetAsBox(
        (size.x / 2 - 5.f) / scale,   
        2.f / scale,              
        b2Vec2(0, (size.y / 2) / scale),
        0.0f
    );

    b2FixtureDef footFixture;
    footFixture.shape = &footShape;
    footFixture.isSensor = true;
    footFixture.filter = filter;
    footFixture.userData.pointer = 1;

    footSensor = body->CreateFixture(&footFixture);
}

void Player::InitializeAnimations()
{
    textures[IDLE] = &SpriteLoader::getTexture(playerIdle);
    textures[MOVE] = &SpriteLoader::getTexture(playerRun);
    textures[PUSH] = &SpriteLoader::getTexture(playerPush);
    textures[PULL] = &SpriteLoader::getTexture(playerPull);
    textures[FALL] = &SpriteLoader::getTexture(playerFall);

    animations[IDLE] = Animation(textures[IDLE], { 4, 1 }, .8);
    animations[MOVE] = Animation(textures[MOVE], { 5, 1 }, animationRate);
    animations[PUSH] = Animation(textures[PUSH], { 2, 1 }, animationRate);
    animations[PULL] = Animation(textures[PULL], { 2, 1 }, animationRate);
    animations[FALL] = Animation(textures[FALL], { 1, 1 }, animationRate);

    sprite.setScale(size.x / animations[IDLE].uvRect.width,
        size.y / animations[IDLE].uvRect.height);
}

void Player::Update(Direction dir, Control control, float deltaTime)
{
    currentState = IDLE;

    bool horizontalMove = (dir == LEFT || dir == RIGHT);
    int dirX = (dir == LEFT ? -1 : (dir == RIGHT ? 1 : 0));

    if (control == INTERACT && interacting && boxBody && onGround)
    {
        if (dirX != 0)
        {
            float gravity = -9.8f;

            float force = boxBody->GetMass() * gravity ;
            float drag = 0;

            float dx = boxBody->GetPosition().x - body->GetPosition().x;

            if ((dx > 0 && dirX > 0) || (dx < 0 && dirX < 0))
                currentState = PUSH;
            else
                currentState = PULL;

            boxBody->ApplyForceToCenter({ force * dirX, 0 }, true);
            body->ApplyForceToCenter({ drag * dirX, 0 }, true);
        }
    }
    else {
        if (!onGround)
        {
            currentState = FALL;
			velocity = fallVelocity;
        }
        else
            velocity = walkVelocity;

        if (horizontalMove)
        {
            Move(dir);
            currentState = MOVE;
        }
       
    }

    UpdateAnimation(deltaTime, dir);
}

void Player::Move(Direction dir)
{
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = velocity * (dir == LEFT ? -1 : 1);
    body->SetLinearVelocity(vel);
}

void Player::UpdateAnimation(float dt, Direction dir)
{
    Animation* animation = &animations[currentState];
    sprite.setTexture(*textures[currentState]);
	int scaleSign = sprite.getScale().x < 0 ? -1 : 1;
   
    if (dir != NOMOVE) scaleSign = (int)dir;
    if (currentState == PULL) scaleSign = -scaleSign;

    sprite.setOrigin(animation->uvRect.width / 2, animation->uvRect.height / 2);
    sprite.setScale(scaleSign * (size.x / animation->uvRect.width),
        size.y / animation->uvRect.height);

    animation->Update(0, dt);
    sprite.setTextureRect(animation->uvRect);

    b2Vec2 pos = body->GetPosition();
    sprite.setPosition(pos.x * scale, pos.y * scale);
}

void Player::BeginContact(b2Contact* contact)
{
    b2Fixture* fA = contact->GetFixtureA();
    b2Fixture* fB = contact->GetFixtureB();

    uint16 cA = fA->GetFilterData().categoryBits;
    uint16 cB = fB->GetFilterData().categoryBits;


    if(cA == SPIKE || cB == SPIKE)
    {
		std::cout << "Player hit spikes!" << std::endl;
        return;
	}

    if(cA == DOOR || cB == DOOR)
    {
        std::cout << "Player reached the door!" << std::endl;
        return;
	}

    if (cA == BOX)
    {
		std::cout << "Player interacting with box" << std::endl;
        boxBody = fA->GetBody();
        interacting = true;
    }
    else if (cB == BOX)
    {
        std::cout << "Player interacting with box" << std::endl;
        boxBody = fB->GetBody();
        interacting = true;
    }

    if (fA == footSensor || fB == footSensor)
    {
        footContacts++;
        onGround = true;
		std::cout << "Player on ground" << std::endl;
    }
}

int Player::GetCollectablesNumber() {
	return collectables;
}

void Player::EndContact(b2Contact* contact) {
    b2Fixture* fA = contact->GetFixtureA();
    b2Fixture* fB = contact->GetFixtureB();

    uint16 cA = fA->GetFilterData().categoryBits;
    uint16 cB = fB->GetFilterData().categoryBits;

    if (cA == BOX|| cB == BOX)
    {
        boxBody = nullptr;
        interacting = false;
    }
    if (fA == footSensor || fB == footSensor)
    {
        footContacts--;
        if (footContacts <= 0)
            onGround = false;
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

Player::~Player() {}