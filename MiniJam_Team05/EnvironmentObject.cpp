#include "EnvironmentObject.h"
#include "SpriteLoader.h"
#include <iostream>

EnvironmentObject::EnvironmentObject(b2World& world, float scale, b2Vec2 position , ObjectType type)
{
    this->world = &world;
    body = nullptr;

    this->scale = scale;
    startPosition = position;

    size = sf::Vector2f(32.f, 32.f);  
    density = 1.0f;
    boxDensity = 1000.f;
    friction = 0.3f;
    animationRate = 0.1f;

	filter.categoryBits = type;
	filter.maskBits = PLAYER|GROUND;

    SetBody();
    SetFixture();
    InitializeAnimations();
}
void EnvironmentObject::SetBody()
{
    b2BodyDef bodyDef;

    if(filter.categoryBits == BOX)
        bodyDef.type = b2_dynamicBody;
	else
        bodyDef.type = b2_staticBody;

    bodyDef.position.Set(startPosition.x / scale, startPosition.y / scale);
    bodyDef.fixedRotation = true;
    body = world->CreateBody(&bodyDef);
}

void EnvironmentObject::SetFixture()
{
    b2PolygonShape boxShape;
    boxShape.SetAsBox((size.x / 2) / scale, (size.y / 2) / scale);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;

    if (filter.categoryBits == BOX)
        fixtureDef.density = boxDensity;
    else
        fixtureDef.density = density;
    
    fixtureDef.friction = friction;
    fixtureDef.filter = filter;

    body->CreateFixture(&fixtureDef);
}

void EnvironmentObject::InitializeAnimations()
{
    if (filter.categoryBits == KEY)
    {
        texture = &SpriteLoader::getTexture(SpriteType::keyIdle);
        idle = Animation(texture, { 5, 1 }, animationRate);
        sprite.setTexture(*texture);
        sprite.setScale(size.x / idle.uvRect.width,
            size.y / idle.uvRect.height);
        sprite.setOrigin(idle.uvRect.width / 2, idle.uvRect.height / 2);
        return;
    }

    if(filter.categoryBits == BOX)
		texture = &SpriteLoader::getTexture(SpriteType::boxSprite);
    else if(filter.categoryBits == SPIKE)
        texture = &SpriteLoader::getTexture(SpriteType::spikeSprite);

    sprite.setTexture(*texture);
    sprite.setScale(size.x / texture->getSize().x,
        size.y / texture->getSize().y);
    sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
}

void EnvironmentObject::Update(float deltaTime)
{
    UpdateAnimation(deltaTime);
    b2Vec2 pos = body->GetPosition();
    sprite.setPosition(pos.x * scale, pos.y * scale);
}

void EnvironmentObject::UpdateAnimation(float deltaTime)
{
    if(filter.categoryBits != static_cast<uint16>(ObjectType::KEY))
		return;
    idle.Update(0, deltaTime);
    sprite.setScale(size.x / idle.uvRect.width,
        size.y / idle.uvRect.height);
    sprite.setOrigin(idle.uvRect.width / 2, idle.uvRect.height / 2);
    sprite.setTextureRect(idle.uvRect);
}

void EnvironmentObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

EnvironmentObject::~EnvironmentObject()
{
}
