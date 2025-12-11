#pragma once
#include "Rotator.h"
#include "Background.h"
#include "Key.h"
#include "Door.h"
#include "Spike.h"

class Level {
    Rotator Level_Rotator;
    Background Level_Background;

    bool rotating;
    float angleStep;
    float targetRotation;
    float totalRotation;
    const float rotationSpeed = 0.8f;
    const float rotationDelay = 3.0f;
    const float rotationAngle = Utilities::Degree_to_Radian(90.0f);

protected:
    vector<unique_ptr<GameObject>> Environment;
    vector<unique_ptr<Spike>> Spikes;
    unique_ptr<Key> Level_Key;
    unique_ptr<Door> Level_Door;

public:
    Level(b2World& world, Texture* Background_Texture);
    ~Level();

    void Update(const float deltaTime, Clock& RotationClock, b2World& world);
    void Draw(RenderWindow& window);
    void CollectKey();
};