#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class SoundManager
{
public:
    static SoundManager& Instance();

    bool LoadSound(const std::string& name, const std::string& filepath);
    void Play(const std::string& name);
    void SetVolume(float volume);

private:
    SoundManager() = default;

    std::unordered_map<std::string, sf::SoundBuffer> buffers;
    std::unordered_map<std::string, sf::Sound> sounds;

    float volume = 100.f;
};
