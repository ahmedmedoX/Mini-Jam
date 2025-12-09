#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <map>


enum SpriteType
{
	playerSprite,
	playerIdle,
	playerRun,
	playerPush,
	playerPull,
	playerFall,
	keyIdle,
	spikeSprite,
	boxSprite,
    Null
};
class SpriteLoader {
public:
    static sf::Texture& getTexture(SpriteType spriteType);

private:
	static std::vector<std::pair<SpriteType, sf::Color>> planetTextures;
	static std::map<SpriteType, sf::Texture> textures;
};
