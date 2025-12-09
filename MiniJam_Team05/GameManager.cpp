#include "GameManager.h"
#include "Ground.h"

GameManager::GameManager()
    : m_window(VideoMode(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT), "SFML Box2D Physics!")
{
    m_window.setFramerateLimit(Utilities::FPS);

    m_world = make_unique<b2World>(b2Vec2(0.f, 9.8f));

    player = std::make_unique<Player>(
        *m_world,
        Utilities::PIXELS_PER_UNIT,                        
        b2Vec2(400.f, 400.f)               
    );

    shared_ptr rockTexture =make_shared<Texture>();
    rockTexture->loadFromFile("Map.jfif");

    m_levelData.push_back({
        [rockTexture](b2World& world) {
            return make_unique<Level_Rock>(world, rockTexture);
        }
        });

    m_currentIndex = 0;
    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);

    m_deltaTime = 0.f;

    dir = Direction::NOMOVE;
    control = Control::NONE;

    m_world->SetContactListener(player.get());

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.f / Utilities::PIXELS_PER_UNIT, 550.f / Utilities::PIXELS_PER_UNIT);
    groundBodyDef.type = b2_staticBody;
    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
    groundBody->SetSleepingAllowed(false);

    b2PolygonShape groundBox;
    groundBox.SetAsBox((800.f / 2) / Utilities::PIXELS_PER_UNIT, (40.f / 2) / Utilities::PIXELS_PER_UNIT);

    b2Filter groundFilter;
    groundFilter.categoryBits = 0x0001;

    b2FixtureDef groundFixture;
    groundFixture.shape = &groundBox;
    groundFixture.friction = 0.3f;
    groundFixture.filter = groundFilter;
    groundBody->CreateFixture(&groundFixture);
    groundRect.setSize(sf::Vector2f(800.f, 40.f));
    groundRect.setOrigin(400.f, 20.f);
    groundRect.setPosition(400.f, 550.f);
    groundRect.setFillColor(Color::Green);
}

GameManager::~GameManager() {}

void GameManager::Run() {
    while (m_window.isOpen()) {
        HandleInput();
        Update();
        Draw();
        if (CheckLevelWin()) {
            if (m_currentIndex >= m_levelData.size()) {
                Win();
                return;
            }
            m_currentIndex++;
            SwitchLevel(m_currentIndex);
        }
    }
}

void GameManager::HandleInput() {
    Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == Event::Closed)
            m_window.close();

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
    
    if (Keyboard::isKeyPressed(Keyboard::R)) {
        RestartLevel();
    }

    if (Keyboard::isKeyPressed(Keyboard::N)) {
        int next = (m_currentIndex + 1) % m_levelData.size();
        SwitchLevel(next);
    }
}

void GameManager::Update() {
    if (m_deltaClock.getElapsedTime().asSeconds() > timeStep) {
        m_world->Step(timeStep, velocityIterations, positionIterations);
        m_deltaTime = m_deltaClock.restart().asSeconds();
    }

    if (m_currentLevel)
        m_currentLevel->Update(m_deltaTime, m_rotationClock, *m_world);

    if (m_box)
        m_box->Update();

    if (player)
     player->Update(dir, control, m_deltaTime);
}

void GameManager::Draw() {
    m_window.clear();

    if (m_currentLevel)
        m_currentLevel->Draw(m_window);

    if (m_box)
        m_box->Draw(m_window);
    m_window.draw(*player.get());
    m_window.draw(groundRect);
    m_window.display();
}

void GameManager::SwitchLevel(int index) {
    if (index >= 0 && index < m_levelData.size()) {
        m_currentIndex = index;
        m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);
        m_deltaClock.restart();
        m_rotationClock.restart();
    }
}

void GameManager::RestartLevel() {
    //m_world = std::make_unique<b2World>(b2Vec2(0.f, -9.8f));

    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);

    m_box = make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 400)),
        *m_world, 2.f, 2.f, 1.5f, true);
    m_box->setFillColor(Color::Green);

    m_deltaClock.restart();
    m_rotationClock.restart();
}

bool GameManager::CheckLevelWin() {
    // TODO: Replace with actual level win logic
    // Example: if player box reaches some position
    if (true) {
        
    }
    return false;
}

void GameManager::Win() {
    // TODO: Replace with actual level win logic
    // Example: if player box reaches some position

}

void GameManager::Death() {

}