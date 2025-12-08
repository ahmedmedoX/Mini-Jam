#include "Rotator.h"
#include "Background.h"

using namespace sf;

int main() {
    b2World* world = new b2World(b2Vec2(0, 9.8f));

    Clock DeltaClock;
    Clock RotationClock;
    float deltaTime = 0;
    float RotationdeltaTime = 0;

    RenderWindow window(VideoMode(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT), "SFML Box2D Physics!");
    window.setFramerateLimit(Utilities::FPS);

    Texture Background_Texture;
    Background_Texture.loadFromFile("D:/ITI/Game Programming Intake 46/Mini Jam/Mini-Jam/MiniJam_Team05/Map.jfif");
    Background background(&Background_Texture);

    vector<GameObject*> Environment;
    Rotator rotator;

    GameObject floor(Utilities::Convert_SFML_Box2D_Space(
        Vector2f(Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT)), *world,
        800 / Utilities::PIXELS_PER_UNIT, 150 / Utilities::PIXELS_PER_UNIT, 0.0f, false);

    GameObject roof(Utilities::Convert_SFML_Box2D_Space(
        Vector2f(Utilities::WINDOW_WIDTH / 2, 0)), *world,
        800 / Utilities::PIXELS_PER_UNIT, 150 / Utilities::PIXELS_PER_UNIT, 0.0f, false);

    GameObject leftWall(Utilities::Convert_SFML_Box2D_Space(
        Vector2f(0, Utilities::WINDOW_HEIGHT / 2)), *world,
        150 / Utilities::PIXELS_PER_UNIT, 800 / Utilities::PIXELS_PER_UNIT, 0.0f, false);

    GameObject rightWall(Utilities::Convert_SFML_Box2D_Space(
        Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT / 2)), *world,
        150 / Utilities::PIXELS_PER_UNIT, 800 / Utilities::PIXELS_PER_UNIT, 0.0f, false);

    Environment.push_back(&floor);
    Environment.push_back(&roof);
    Environment.push_back(&leftWall);
    Environment.push_back(&rightWall);

    b2Vec2 roomCenter(0, 0);

    bool rotating = false;
    float targetRotation = 0.0f;
    float totalRotation = 0.0f;
    const float rotationSpeed = 2.0f;
    const float rotationAngle = Utilities::Degree_to_Radian(90.0f);

    const float timeStep = 1.0f / (float)Utilities::FPS;

    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;

    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!rotating) {
            if (RotationClock.getElapsedTime().asSeconds() >= 2.0f) {
                rotating = true;
                totalRotation = 0.f;
                targetRotation = rotationAngle;
            }
        }

        if (rotating) {
            float angleStep = rotationSpeed * deltaTime;
            if (totalRotation + angleStep >= targetRotation)
            {
                angleStep = targetRotation - totalRotation;
                rotating = false;
                RotationClock.restart();
            }
            totalRotation += angleStep;
            rotator.RotateLevel(Environment, *world, roomCenter, angleStep);
            background.Update(angleStep);
        }

        if (DeltaClock.getElapsedTime().asSeconds() > timeStep) {
            world->Step(timeStep, velocityIterations, positionIterations);
            deltaTime = DeltaClock.restart().asSeconds();
        }

        for (int i = 0; i < Environment.size(); i++) {
            Environment[i]->Update();
        }

        window.clear();

        for (int i = 0; i < Environment.size(); i++) {
            Environment[i]->Draw(window);
        }
        background.Draw(window);

        window.display();
    }

    return 0;
}