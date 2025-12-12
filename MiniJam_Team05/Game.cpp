//#include "Level_Rock.h"
//
//const float timeStep = 1.0f / (float)Utilities::FPS;
//
//const int32 velocityIterations = 8;
//const int32 positionIterations = 3;
//
//int main() {
//    b2World* world = new b2World(b2Vec2(0, -9.8f));
//
//    Clock DeltaClock;
//    Clock RotationClock;
//    float deltaTime = 0;
//    float RotationdeltaTime = 0;
//
//    RenderWindow window(VideoMode(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT), "SFML Box2D Physics!");
//    window.setFramerateLimit(Utilities::FPS);
//
//    Texture* Rock_Level_Texture = new Texture();
//    Rock_Level_Texture->loadFromFile("Map.jfif");
//
//    Level_Rock level(*world, Rock_Level_Texture);
//
//    GameObject box(Utilities::Convert_SFML_Box2D_Space(
//        Vector2f(400, 400)), *world, 2, 2, 1.5f, true);
//    box.setFillColor(Color::Green);
//
//    while (window.isOpen()) {
//
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        if (DeltaClock.getElapsedTime().asSeconds() > timeStep) {
//            world->Step(timeStep, velocityIterations, positionIterations);
//            deltaTime = DeltaClock.restart().asSeconds();
//        }
//
//        level.Update(deltaTime, RotationClock, *world);
//
//        window.clear();
//
//        level.Draw(window);
//
//        window.display();
//    }
//    return 0;
//}

#include "GameManager.h"

int main() {
    GameManager game;
    game.Run();
    return 0;
}