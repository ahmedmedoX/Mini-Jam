#include <SFML/Graphics.hpp>
#include <Box2D/box2d.h>
#include "Player.h"
#include "EnvironmentObject.h"
#include "Enums.h" 
#include "Cell.h"
#include <list>
#include "Level.h"

#define SCALE 30.f
#define TIME_STEP 1.f / 60.f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3

int main()
{  
    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D + SFML");
	//window.setFramerateLimit(60);
    std::list<EnvironmentObject> keys;

    b2Vec2 gravity(0.f, 9.8f/SCALE);
    b2World world(gravity);
	EnvironmentObject box(world, SCALE, b2Vec2(300, 500),sf::Vector2f(32.f , 32.f), ObjectType::BOX);

	Level level(world, SCALE);  

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

		player.Update(world, dir , control , deltaTime);
		box.Update(deltaTime);  

		level.Update();
		
		

        window.clear(sf::Color::White);
		window.draw(level);
        window.draw(player);
        window.draw(box);
        window.display();
    }

    return 0;
}
