#include "SpriteLoader.h"
#include "FilePathes.h"
#include <random>

std::map<SpriteType, sf::Texture> SpriteLoader::textures;

sf::Texture& SpriteLoader::getTexture(SpriteType spriteType)
{
    if (textures.find(spriteType) != textures.end())
        return textures[spriteType];

    sf::Texture texture;
    std::string path;
    
    if(spriteType == SpriteType::playerIdle)
    {
        path = FilePathes::playerIdle;
    }
    else if (spriteType == SpriteType::playerRun) {
        path = FilePathes::playerRun;
	}
    else if(spriteType == SpriteType::playerPush) {
        path = FilePathes::playerPush;
    }
    else if (spriteType == SpriteType::playerPull) {
        path = FilePathes::playerPull;
	}
    else if(spriteType == SpriteType::playerFall) {
        path = FilePathes::playerFall;
    }
    else if (spriteType == SpriteType::playerDie) {
		path = FilePathes::playerDie;
    }
    else if(spriteType == SpriteType::playerSprite) {
        path = FilePathes::player;
    }


    texture.loadFromFile(path);
    textures[spriteType] = texture;

    return textures[spriteType];
}

