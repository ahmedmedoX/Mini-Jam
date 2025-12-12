#pragma once
#include "Rotator.h"
#include "Background.h"
#include "Key.h"
#include "Door.h"
#include "Spike.h"

class Level {
    Rotator Level_Rotator;
    Background Level_Background;

    bool play = false;
    bool rotating;
    bool Play_Music = true;

    float angleStep;
    float targetRotation;
    float totalRotation;

    float rotationSpeed;
    float rotationDelay;
    float rotationAngle;
    CircleShape timer;
    CircleShape timer_Background;

protected:
    vector<unique_ptr<GameObject>> Environment;
    vector<unique_ptr<Spike>> Spikes;
    unique_ptr<Key> Level_Key;
    unique_ptr<Door> Level_Door;

public:
    Level(b2World& world, Texture* Background_Texture, Texture* Level_Texture);
    ~Level();

    void Update(const float deltaTime, Clock& RotationClock, b2World& world);
    void Draw(RenderWindow& window);
    void CollectKey();
};