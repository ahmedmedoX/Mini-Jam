#include "Level.h"
#include "FilePathes.h"
#include "SoundManager.h"
#include <iostream>

Level::Level(b2World &world, Texture* Level_Texture, Texture* Background_Texture) :
    Level_Background(Level_Texture, Background_Texture)
{
    //Environment.push_back(std::make_unique<GameObject>(
    //    Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT - 80)),
    //    world, 704.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
    //    2.0f, false, GROUND));

    //Environment.push_back(std::make_unique<GameObject>(
    //    Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH / 2, 80)),
    //    world, 704.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
    //    2.0f, false, GROUND));

    //Environment.push_back(std::make_unique<GameObject>(
    //    Utilities::Convert_SFML_Box2D_Space(Vector2f(80, Utilities::WINDOW_HEIGHT / 2)),
    //    world, 64.f / Utilities::PIXELS_PER_UNIT, 704.f / Utilities::PIXELS_PER_UNIT,
    //    5.0f, false, GROUND));

    //Environment.push_back(std::make_unique<GameObject>(
    //    Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH - 80, Utilities::WINDOW_HEIGHT / 2)),
    //    world, 64.f / Utilities::PIXELS_PER_UNIT, 704.f / Utilities::PIXELS_PER_UNIT,
    //    2.0f, false, GROUND));

    SoundManager::Instance().LoadSound("key_Audio", "assets/Audio/key-sound.mp3");
    SoundManager::Instance().LoadSound("rotation_Audio", "assets/Audio/rotation-sound.mp3");

    rotating = false;
    targetRotation = 0.0f;
    totalRotation = 0.0f;
    angleStep = 0.0f;

    SoundManager::Instance().LoadSound("Level_Music", "assets/Audio/xXTFCNSANewAdventureFinalVersion2bXx.mp3");
    SoundManager::Instance().SetLoop("Level_Music", true);
    SoundManager::Instance().SetVolume("Level_Music", 70);

    rotationSpeed = (5.0f + (rand() % 3)) / 10.0f;
    rotationDelay = 5.0f + (rand() % 3);
    rotationAngle = Utilities::Degree_to_Radian(90.0f);

    timer.setRadius(25);
    timer.setOrigin(25, 25);
    timer.setPosition(750, 750);
    timer_Background.setRadius(28);
    timer_Background.setOrigin(28, 28);
    timer_Background.setPosition(750, 750);
    timer_Background.setFillColor(Color::Black);
}

Level::~Level() {
    Environment.clear();
    //Level_Key.reset();
}

void Level::Update(const float deltaTime, Clock& RotationClock, b2World& world) {
    if (Play_Music) {
        SoundManager::Instance().Play("Level_Music");
        Play_Music = false;
    }

    if (!rotating) {
        if (RotationClock.getElapsedTime().asSeconds() >= rotationDelay) {
            rotationSpeed = (8.0f + (rand() % 3)) / 10.0f;
            rotationDelay = 4.0f + (rand() % 3);
            rotating = true;
            totalRotation = 0.f;
            targetRotation = rotationAngle;
            play = true;
        }
        //timer.setFillColor(Color(x * 255.0f, (1.0f - x) * 255.0f, 0, 255));
        timer.setFillColor(Utilities::HSV_to_RGB(
            RotationClock.getElapsedTime().asSeconds() / rotationDelay * 119.0f));
    }

    if (rotating) {
        angleStep = rotationSpeed * deltaTime;
        if (totalRotation + angleStep >= targetRotation) {
            angleStep = targetRotation - totalRotation;
            rotating = false;
            RotationClock.restart();
        }
        totalRotation += angleStep;
        Level_Rotator.RotateLevel(Environment, angleStep);
        Level_Rotator.RotateSpike(Spikes, angleStep);
        Level_Rotator.RotateKey(Level_Key, angleStep);
        Level_Rotator.RotateDoor(Level_Door, angleStep);
        Level_Background.Update(angleStep);
        if (play) {
            SoundManager::Instance().Play("rotation_Audio");
            play = false;
        }

        timer.setFillColor(Color::Green);
    }

    for (int i = 0; i < Environment.size(); i++) {
        Environment[i]->Update();
    }

    if (Level_Key)
        Level_Key->Update(deltaTime);

    if (Level_Door)
        Level_Door->Update();

    for (int i = 0; i < Spikes.size(); i++) {
        Spikes[i]->Update();
    }
}

void Level::Draw(RenderWindow& window) {
    Level_Background.Draw(window);

    for (int i = 0; i < Environment.size(); i++) {
        Environment[i]->Draw(window);
    }

    if(Level_Key)
        Level_Key->Draw(window);

    if(Level_Door)
        Level_Door->Draw(window);

    for (int i = 0; i < Spikes.size(); i++) {
        Spikes[i]->Draw(window);
    }

    window.draw(timer_Background);
    window.draw(timer);
}

void Level::CollectKey() {
    if (Level_Key) {
        Level_Key.reset();
        SoundManager::Instance().Play("key_Audio");
    }
}