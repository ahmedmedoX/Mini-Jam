#include "Cell.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>	
#include "SpriteLoader.h"	
#include "Enums.h"	

Cell::Cell( sf::Vector2f size, b2Vec2 worldPosition)
    : cellSize(size)
{
    this->position = worldPosition;
	this->rotation = 0.f;

    SetTexture();
    Update();
}

void Cell::SetTexture()
{
    texture = &SpriteLoader::getTexture(SpriteType::caveTile);

    sprite.setTexture(*texture);

    sprite.setOrigin(texture->getSize().x * 0.5f, texture->getSize().y * 0.5f);

    sprite.setScale(
        cellSize.x / texture->getSize().x,
        cellSize.y / texture->getSize().y
    );
}

void Cell::Update()
{
    float pixelX = position.x;
    float pixelY = position.y;

    sprite.setPosition(pixelX, pixelY);
    sprite.setRotation(rotation);
}

void Cell::SetPosition(b2Vec2 pos)
{
    position = pos; 
	Update();
}
void Cell::setRotation(float angle)
{
    rotation = angle;
	Update();    
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

Cell::~Cell()
{
}
