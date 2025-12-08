#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cstdlib>
#include <ctime>
#include "GameObject.h"
#include "Rotator.h"
#include <iostream>
static const float SCALE = 30.f;


sf::Color randomColor()
{
    return sf::Color(
        50 + rand() % 206,   // avoid too-dark walls
        50 + rand() % 206,
        50 + rand() % 206
    );
}
inline float degToRad(float deg)
{
    return deg * 3.14159265f / 180.f;
}

float rotationAmount = degToRad(90.f);

int main()
{
    srand(static_cast<unsigned>(time(0)));
    
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Rotating Room");
    window.setFramerateLimit(60);

    b2World world({ 0.f,9.8f });
    // ROOM SETTINGS
    vector<GameObject*> rotatableObjects;
    Rotator rotator;


    float ROOM_W = 900.f;
    float ROOM_H = 900.f;
    float WALL = 40.f;

    float ROOM_X = (1600.f - ROOM_W) / 2.f; 
    float ROOM_Y = 0.f;                      

   
    GameObject player(world,
        { 600 , 250 },
        { 50, 50 },
        true
    );


    player.setFillColor(sf::Color::Blue);


    GameObject floor(world,
        { ROOM_X + ROOM_W / 2.f, ROOM_H - WALL / 2.f },
        { ROOM_W, WALL }, false);
    floor.setFillColor(randomColor());
    rotatableObjects.push_back(&floor);

    GameObject roof(world,
        { ROOM_X + ROOM_W / 2.f, WALL / 2.f },
        { ROOM_W, WALL }, false);
    roof.setFillColor(randomColor());
    rotatableObjects.push_back(&roof);

    GameObject leftWall(world,
        { ROOM_X + WALL / 2.f, ROOM_H / 2.f },
        { WALL, ROOM_H }, false);
    leftWall.setFillColor(randomColor());
    rotatableObjects.push_back(&leftWall);

    GameObject rightWall(world,
        { ROOM_X + ROOM_W - WALL / 2.f, ROOM_H / 2.f },
        { WALL, ROOM_H }, false);
    rightWall.setFillColor(randomColor());
    rotatableObjects.push_back(&rightWall);

    GameObject bta3(world,
        { 600, 300 },  
        { 100, 20 },    
        false);

    rightWall.setFillColor(randomColor());
    rotatableObjects.push_back(&bta3);


    float totalRotation = 0.f;
    float rotationSpeed = 2.0f; 
    bool rotating = false;

    sf::Clock rotateClock;

    b2Vec2 roomCenter(
        (ROOM_X + ROOM_W / 2.f) / SCALE,
        (ROOM_H / 2.f) / SCALE
    );

    sf::Clock dtClock;
   
    float M_PI = 3.14f;
    float targetRotation = 0; 
    float rotationAmount = degToRad(90.f);

 
    while (window.isOpen())
    {
        float dt = dtClock.restart().asSeconds();

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
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
            float angleStep = rotationSpeed * dt;

            // If rotating too far, clamp to target exactly
            if (totalRotation + angleStep >= targetRotation)
            {
                angleStep = targetRotation - totalRotation;
                rotating = false; 
            }

            totalRotation += angleStep;

            rotator.RotatLevel(rotatableObjects, world, roomCenter, angleStep);

          
        }


        world.Step(1 / 60.f, 8, 3);

        player.update();
        floor.update();
        roof.update();
        leftWall.update();
        rightWall.update();
        bta3.update();

        window.clear(sf::Color::Black);

        window.draw(player);
        window.draw(floor);
        window.draw(roof);
        window.draw(leftWall);
        window.draw(rightWall);
		window.draw(bta3);

        window.display();
    }

    return 0;
}
