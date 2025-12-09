#include "Level.h"

Level::Level(b2World &world, std::shared_ptr<sf::Texture> bg) :
    background(bg)
{

    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT - 80)),
        world, 704.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT, 2.0f, false
    ));

    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH / 2, 80)),
        world, 704.f / Utilities::PIXELS_PER_UNIT, 64.f / Utilities::PIXELS_PER_UNIT, 2.0f, false
    ));

    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(80, Utilities::WINDOW_HEIGHT / 2)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 704.f / Utilities::PIXELS_PER_UNIT, 5.0f, false
    ));

    Environment.push_back(std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(Utilities::WINDOW_WIDTH - 80, Utilities::WINDOW_HEIGHT / 2)),
        world, 64.f / Utilities::PIXELS_PER_UNIT, 704.f / Utilities::PIXELS_PER_UNIT, 2.0f, false
    ));

    rotating = false;
    targetRotation = 0.0f;
    totalRotation = 0.0f;
    angleStep = 0.0f;
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
    for (int i = 0; i < Environment.size(); i++) {
        Environment[i]->Draw(window);
    }
    background.Draw(window);
}