#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <map>

enum SpriteType {
	playerSprite,
	playerIdle,
	playerRun,
	playerPush,
	playerPull,
	playerFall,
	keyIdle,
	spikeSprite,
	boxSprite,
	doorSprite,
	Level1,
	Level2,
	//Level3,
    Null
};

class SpriteLoader {
	static std::map<SpriteType, sf::Texture> textures;
public:
    static sf::Texture& getTexture(SpriteType spriteType);
};