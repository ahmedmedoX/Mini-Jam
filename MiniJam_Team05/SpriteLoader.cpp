#include "SpriteLoader.h"
#include "FilePathes.h"

std::map<SpriteType, sf::Texture> SpriteLoader::textures;

sf::Texture& SpriteLoader::getTexture(SpriteType spriteType) {
    auto it = textures.find(spriteType);
    if (it != textures.end())
        return it->second;

    auto& tex = textures[spriteType];
    std::string path;

    switch (spriteType)
    {
    case SpriteType::playerIdle: path = FilePathes::playerIdle; break;
    case SpriteType::playerRun:  path = FilePathes::playerRun;  break;
    case SpriteType::playerPush: path = FilePathes::playerPush; break;
    case SpriteType::playerPull: path = FilePathes::playerPull; break;
    case SpriteType::playerFall: path = FilePathes::playerFall; break;
    case SpriteType::playerSprite: path = FilePathes::player; break;

    case SpriteType::boxSprite:  path = FilePathes::boxSprite;  break;
    case SpriteType::spikeSprite:  path = FilePathes::spikeSprite;  break;
    case SpriteType::keyIdle:  path = FilePathes::keyIdle;  break;
    case SpriteType::doorSprite:  path = FilePathes::doorSprite;  break;

    case SpriteType::Level1:  path = FilePathes::Level1_Background;  break;
    case SpriteType::Level2:  path = FilePathes::Level2_Background;  break;
    //case SpriteType::Level3:  path = FilePathes::Level3_Background;  break;
    }

    if (!tex.loadFromFile(path))
        std::cerr << "Failed to load texture: " << path << "\n";

    return tex;
}


