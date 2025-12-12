#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::Instance()
{
    static SoundManager instance;
    return instance;
}

bool SoundManager::LoadSound(const std::string& name, const std::string& filepath)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath))
    {
        std::cout << "Failed to load sound: " << filepath << "\n";
        return false;
    }

    buffers[name] = buffer;

    sf::Sound sound;
    sound.setBuffer(buffers[name]);
    sound.setVolume(volume);

    sounds[name] = sound;

    return true;
}

void SoundManager::Play(const std::string& name)
{
    if (sounds.find(name) != sounds.end())
    {
        sounds[name].play();
    }
    else
    {
        std::cout << "Sound not found: " << name << "\n";
    }
}

void SoundManager::Stop(const std::string& name)
{
    if (sounds.find(name) != sounds.end())
    {
        sounds[name].stop();
    }
    else
    {
        std::cout << "Sound not found: " << name << "\n";
    }
}

void SoundManager::SetVolume(float vol)
{
    volume = vol;

    for (auto& s : sounds)
    {
        s.second.setVolume(vol);
    }
}

void SoundManager::SetVolume(const std::string& name, float vol)
{
    if (sounds.find(name) != sounds.end())
    {
        sounds[name].setVolume(vol);
    }
    else
    {
        std::cout << "Sound not found: " << name << "\n";
    }
}

void SoundManager::SetLoop(const std::string& name, const bool loop) {
    if (sounds.find(name) != sounds.end())
    {
        sounds[name].setLoop(loop);
    }
    else
    {
        std::cout << "Sound not found: " << name << "\n";
    }
}

void SoundManager::StopAll()
{
    for (auto& s : sounds)
    {
        s.second.stop();
    }
}