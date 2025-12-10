#include <SFML/Graphics.hpp>
#include <Box2D/box2d.h>
#include "Player.h"
#include "EnvironmentObject.h"
#include "Enums.h"  
#include <list>

#define SCALE 30.f
#define TIME_STEP 1.f / 60.f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3

int main()
{
   
    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D + SFML");
	//window.setFramerateLimit(60);
    std::list<EnvironmentObject> keys;

    float rotationTimer = 0.f;
    float rotationInterval = 5.f; // 5 seconds
    float rotationAngle = 90.f;   // Rotate 90°

    b2Vec2 gravity(0.f, 9.8f/SCALE);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.f / SCALE, 550.f / SCALE);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox((800.f / 2) / SCALE, (40.f / 2) / SCALE);

	b2Filter groundFilter;
	groundFilter.categoryBits = 0x0001;

    b2FixtureDef groundFixture;
    groundFixture.shape = &groundBox;
    groundFixture.friction = 0.7f;
	groundFixture.filter = groundFilter;
    groundBody->CreateFixture(&groundFixture);

   
    sf::RectangleShape groundRect(sf::Vector2f(800.f, 40.f));
    groundRect.setOrigin(400.f, 20.f);
    groundRect.setPosition(400.f, 550.f);
    groundRect.setFillColor(sf::Color::Green);

    // LEFT WALL
    b2BodyDef leftBodyDef;
    leftBodyDef.position.Set(20.f / SCALE, 300.f / SCALE); // center of left wall
    b2Body* leftBody = world.CreateBody(&leftBodyDef);

    b2PolygonShape leftBox;
    leftBox.SetAsBox((40.f / 2) / SCALE, (600.f / 2) / SCALE);

    b2Filter leftFilter;
    leftFilter.categoryBits = 0x0001;

    b2FixtureDef leftFixture;
    leftFixture.shape = &leftBox;
    leftFixture.friction = 0.7f;
    leftFixture.filter = leftFilter;
    leftBody->CreateFixture(&leftFixture);

    sf::RectangleShape leftRect(sf::Vector2f(40.f, 600.f));
    leftRect.setOrigin(20.f, 300.f);
    leftRect.setPosition(20.f, 300.f);
    leftRect.setFillColor(sf::Color::Green);


    // RIGHT WALL
    b2BodyDef rightBodyDef;
    rightBodyDef.position.Set(780.f / SCALE, 300.f / SCALE);
    b2Body* rightBody = world.CreateBody(&rightBodyDef);

    b2PolygonShape rightBox;
    rightBox.SetAsBox((40.f / 2) / SCALE, (600.f / 2) / SCALE);

    b2Filter rightFilter;
    rightFilter.categoryBits = 0x0001;

    b2FixtureDef rightFixture;
    rightFixture.shape = &rightBox;
    rightFixture.friction = 0.7f;
    rightFixture.filter = rightFilter;
    rightBody->CreateFixture(&rightFixture);

    sf::RectangleShape rightRect(sf::Vector2f(40.f, 600.f));
    rightRect.setOrigin(20.f, 300.f);
    rightRect.setPosition(780.f, 300.f);
    rightRect.setFillColor(sf::Color::Green);


    // TOP WALL
    b2BodyDef topBodyDef;
    topBodyDef.position.Set(400.f / SCALE, 20.f / SCALE);
    b2Body* topBody = world.CreateBody(&topBodyDef);

    b2PolygonShape topBox;
    topBox.SetAsBox((800.f / 2) / SCALE, (40.f / 2) / SCALE);

    b2Filter topFilter;
    topFilter.categoryBits = 0x0001;

    b2FixtureDef topFixture;
    topFixture.shape = &topBox;
    topFixture.friction = 0.7f;
    topFixture.filter = topFilter;
    topBody->CreateFixture(&topFixture);

    sf::RectangleShape topRect(sf::Vector2f(800.f, 40.f));
    topRect.setOrigin(400.f, 20.f);
    topRect.setPosition(400.f, 20.f);
    topRect.setFillColor(sf::Color::Green);



	EnvironmentObject key(world, SCALE, b2Vec2(500, 500), ObjectType::KEY);
	EnvironmentObject box(world, SCALE, b2Vec2(300, 500), ObjectType::BOX);
	EnvironmentObject door(world, SCALE, b2Vec2(700, 500), ObjectType::DOOR);
	keys.push_back(key);


    Player player(world, SCALE, b2Vec2(400, 100) );
	Direction dir = Direction::NOMOVE;
    Control control = Control::NONE;

	world.SetContactListener(&player);

	sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::F) {
                    control = Control::INTERACT;
                }

                if (event.key.code == sf::Keyboard::A) {
                    dir = Direction::LEFT;
                }
                else if (event.key.code == sf::Keyboard::D) {
                    dir = Direction::RIGHT;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
					dir = Direction::NOMOVE;
                }
                if (event.key.code == sf::Keyboard::F) {
                    control = Control::NONE;
                }
			}

        }
        world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		float deltaTime = clock.restart().asSeconds();  
		player.Update(dir , control , deltaTime);
		box.Update(deltaTime);  
        for (auto& it : keys)
        {
            it.Update(deltaTime);
        }
		door.Update(deltaTime);

        window.clear(sf::Color::White);
        window.draw(groundRect);
		window.draw(leftRect);
		window.draw(rightRect);
		window.draw(topRect);
        window.draw(player);
        for (auto& it : keys)
        {
			window.draw(it);    
        }
        window.draw(box);
		window.draw(door);
        window.display();
    }

    return 0;
}
