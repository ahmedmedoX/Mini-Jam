#include <SFML/Graphics.hpp>
#include <Box2D/box2d.h>
#include "Player.h"

#define SCALE 30.f
#define TIME_STEP 1.f / 60.f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D + SFML");

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


    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.position.Set(400.f / SCALE, 100.f / SCALE);
    b2Body* boxBody = world.CreateBody(&boxBodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox((40.f / 2) / SCALE, (40.f / 2) / SCALE);

	b2Filter boxFilter;
	boxFilter.categoryBits = 0x0004;

    b2FixtureDef boxFixture;
    boxFixture.shape = &boxShape;
    boxFixture.density = 500.f;
    boxFixture.friction = 0.3f;
	boxFixture.filter = boxFilter;  
    boxBody->CreateFixture(&boxFixture);
    sf::RectangleShape boxRect(sf::Vector2f(40.f, 40.f));
    boxRect.setOrigin(20.f, 20.f);
    boxRect.setFillColor(sf::Color::Blue);


    Player player(world, SCALE, b2Vec2(400, 100) , groundFilter , boxFilter);
	Direction dir = Direction::IDLE;
    Control control = Control::NONE;

	world.SetContactListener(&player);

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
					dir = Direction::IDLE;
                }
                if (event.key.code == sf::Keyboard::F) {
                    control = Control::NONE;
                }
			}

        }

        world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

		player.Update(dir , control);

		b2Vec2 boxPosition = boxBody->GetPosition();
		boxRect.setPosition(boxPosition.x * SCALE, boxPosition.y * SCALE);

        window.clear();
        window.draw(groundRect);
        window.draw(player);
		window.draw(boxRect);
        window.display();
    }

    return 0;
}
