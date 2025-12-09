#pragma once
#include "Rotator.h"
#include "Background.h"

class Level {
    Rotator rotator;
    Background background;
    const b2Vec2 roomCenter = b2Vec2_zero;
    bool rotating;
    float angleStep;
    float targetRotation;
    float totalRotation;

protected:
    std::vector<std::unique_ptr<GameObject>> Environment;
    const float rotationSpeed = 1.0f;
    const float rotationDelay = 2.0f;
    const float rotationAngle = Utilities::Degree_to_Radian(90.0f);

public:
    Level(b2World& world, std::shared_ptr<sf::Texture> bg);
    ~Level();

    void Update(const float deltaTime, Clock& RotationClock, b2World& world);
    void Draw(RenderWindow& window);
};