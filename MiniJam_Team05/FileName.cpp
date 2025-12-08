#include "GameObject.h"
#include "Rotator.h"
using namespace sf;
inline float degToRad(float deg)
{
    return deg * 3.14159265f / 180.f;
}

float rotationAmount = degToRad(90.f);

int main() {
    b2World* world = new b2World(b2Vec2(0, 9.8f));

    const float timeStep = 1.0f / (float)Utilities::FPS;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    Clock clock;
    float deltaTime = 0;

    RenderWindow window(VideoMode(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT), "SFML Box2D Physics!");
    window.setFramerateLimit(Utilities::FPS);

    Texture tex;
    tex.loadFromFile("D:/ITI/Game Programming Intake 46/OOP for Game Development/SFML Project/Textures/Environment/Rock_Tile.png");

    Vector2f x(400.0f, 400.0f);
    GameObject obj(Utilities::Convert_SFML_Box2D_Space(x), *world, &tex, 4.0f, 4.0f, 0.0f);

    vector<GameObject*> rotatableObjects;
    Rotator rotator;
    float ROOM_W = 900.f;
    float ROOM_H = 900.f;
    float WALL = 40.f;

    float ROOM_X = (1600.f - ROOM_W) / 2.f;
    float ROOM_Y = 0.f;
    rotatableObjects.push_back(&obj);
    float totalRotation = 0.f;
    float rotationSpeed = 2.0f;
    bool rotating = false;
    b2Vec2 roomCenter(
        (ROOM_X + ROOM_W / 2.f) / Utilities::PIXELS_PER_UNIT,
        (ROOM_H / 2.f) / Utilities::PIXELS_PER_UNIT
    );
    float M_PI = 3.14f;
    float targetRotation = 0;
    float rotationAmount = 0.2f;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!rotating)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                rotating = true;
                totalRotation = 0.f;
                targetRotation = rotationAmount;
            }
        }


        if (rotating)
        {
            float angleStep = rotationSpeed * deltaTime;

            // If rotating too far, clamp to target exactly
            if (totalRotation + angleStep >= targetRotation)
            {
                angleStep = targetRotation - totalRotation;
                rotating = false;
            }
            totalRotation += angleStep;
            rotator.RotatLevel(rotatableObjects, *world, roomCenter, angleStep);
        }
        world->Step(1 / 60.f, 8, 3);
        obj.Update();

        window.clear();
        obj.Draw(window);
        window.display();
    }

    return 0;
}