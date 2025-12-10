#include "Level.h"
#define PI 3.14159265

Level::Level(b2World& world, float scale)
{
	SetWalls(world, scale);
	SetPlatforms(world, scale);
}


void Level::SetWalls(b2World& world, float scale )
{
	Platform leftWall(world, scale,15, sf::Vector2f(32.f, 32.f), b2Vec2(-160, 296));
	leftWall.setRotation(90);
	platforms.push_back(leftWall);

	Platform rightWall(world, scale, 15, sf::Vector2f(32.f, 32.f), b2Vec2(480, 296));
	rightWall.setRotation(90);
	platforms.push_back(rightWall);

	Platform  bottomWall(world, scale, 21, sf::Vector2f(32.f, 32.f), b2Vec2(80, 530));
	platforms.push_back(bottomWall);

	Platform  topWall(world, scale, 21, sf::Vector2f(32.f, 32.f), b2Vec2(80, 40));
	platforms.push_back(topWall);

}
void Level::SetPlatforms(b2World& world, float scale )
{
	
}
void Level::Update()
{	
	for (auto& platform : platforms)
	{
		platform.Update();
	}
}
void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& platform : platforms)
	{
		target.draw(platform, states);
	}
}
Level::~Level()
{

}
