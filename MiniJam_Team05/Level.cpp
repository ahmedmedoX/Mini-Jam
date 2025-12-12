#include "Level.h"
#include "FilePathes.h"

Level::Level(b2World &world, Texture* Level_Texture, Texture* Background_Texture) :
    Level_Background(Level_Texture, Background_Texture)
{
    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT - 80)),
        world, 704.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH / 2, 80)),
        world, 704.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(80, Utilities::WINDOW_HEIGHT / 2)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 704.f / Utilities::PIXELS_PER_UNIT,
        5.0f, false, GROUND));

    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH - 80, Utilities::WINDOW_HEIGHT / 2)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 704.f / Utilities::PIXELS_PER_UNIT,
        2.0f, false, GROUND));

    rotating = false;
    targetRotation = 0.0f;
    totalRotation = 0.0f;
    angleStep = 0.0f;
}

Level::~Level() {
    Environment.clear();
    //Level_Key.reset();
}

void Level::Update(const float deltaTime, Clock& RotationClock, b2World& world) {
    if (!rotating) {
        if (RotationClock.getElapsedTime().asSeconds() >= rotationDelay) {
            rotating = true;
            totalRotation = 0.f;
            targetRotation = rotationAngle;
        }
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
}

void Level::CollectKey() {
    if(Level_Key)
        Level_Key.reset();
}