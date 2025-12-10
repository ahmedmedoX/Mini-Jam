#pragma once
#include "Rotator.h"
#include "Background.h"
#include "Key.h"
#include "Door.h"

class Level {
    Rotator rotator;
    Background background;
    const b2Vec2 roomCenter = b2Vec2_zero;
    bool rotating;
    float angleStep;
    float targetRotation;
    float totalRotation;

protected:
    vector<unique_ptr<GameObject>> Environment;
    unique_ptr<Key> Level_Key;
    unique_ptr<Door> Level_Door;

    const float rotationSpeed = 0.8f;
    const float rotationDelay = 3.0f;
    const float rotationAngle = Utilities::Degree_to_Radian(90.0f);

    Texture* Key_Texture;
    Texture* Box_Texture;
    Texture* Door_Texture;

public:
    Level(b2World& world, Texture* Background_Texture);
    ~Level();

    void Update(const float deltaTime, Clock& RotationClock, b2World& world);
    void Draw(RenderWindow& window);
    void CollectKey();
};