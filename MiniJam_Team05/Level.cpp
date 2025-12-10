#include "Level.h"
#include "FilePathes.h"

Level::Level(b2World &world, Texture* Background_Texture) :
    background(Background_Texture)
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

    Key_Texture = new Texture();
    Key_Texture->loadFromFile(FilePathes::keyIdle);

    Box_Texture = new Texture();
    Box_Texture->loadFromFile(FilePathes::boxSprite);

    Door_Texture= new Texture();
    Door_Texture->loadFromFile(FilePathes::door);
}

Level::~Level() {
    Environment.clear();
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
        rotator.RotateLevel(Environment, world, roomCenter, angleStep);
        background.Update(angleStep);
    }

    for (int i = 0; i < Environment.size(); i++) {
        Environment[i]->Update();
    }
}

void Level::Draw(RenderWindow& window) {
    background.Draw(window);
    for (int i = 0; i < Environment.size(); i++) {
        Environment[i]->Draw(window);
    }
}