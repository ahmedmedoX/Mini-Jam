#include "GameManager.h"

GameManager::GameManager()
    : m_window(VideoMode(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT), "SFML Box2D Physics!")
{
    m_window.setFramerateLimit(Utilities::FPS);

    m_world = make_unique<b2World>(b2Vec2(0.f, -9.8f));

    shared_ptr rockTexture = std::make_shared<sf::Texture>();
    rockTexture->loadFromFile("Map.jfif");

    shared_ptr rockTexture1 = std::make_shared<sf::Texture>();
    rockTexture1->loadFromFile("Cave Tile.png");

    m_levelData.push_back({
        [rockTexture](b2World& world) {
            return std::make_unique<Level_Rock>(world, rockTexture);
        }
        });

    m_levelData.push_back({
    [rockTexture1](b2World& world) {
        return std::make_unique<Level_Forest>(world, rockTexture1);
    }
        });

    m_currentIndex = 0;
    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);

    m_box = make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 400)),
        *m_world, 2.f, 2.f, 1.5f, true);

    m_box->setFillColor(Color::Green);

    m_deltaTime = 0.f;
}

GameManager::~GameManager() {}

void GameManager::Run() {
    while (m_window.isOpen()) {
        HandleInput();
        Update();
        Draw();
        if (CheckWin()) {
            m_currentIndex++;
            if (m_currentIndex < m_levelData.size())
                SwitchLevel(m_currentIndex);
            else
                RestartLevel();
        }
    }
}

void GameManager::HandleInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
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
}

void GameManager::Draw() {
    m_window.clear();

    if (m_currentLevel)
        m_currentLevel->Draw(m_window);

    if (m_box)
        m_box->Draw(m_window);

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
    m_box = std::make_unique<GameObject>(
        Utilities::Convert_SFML_Box2D_Space(sf::Vector2f(400, 400)),
        *m_world, 2.f, 2.f, 1.5f, true
    );
    m_box->setFillColor(sf::Color::Green);
    m_deltaClock.restart();
    m_rotationClock.restart();
}

bool GameManager::CheckWin() {
    // TODO: Replace with actual level win logic
    // Example: if player box reaches some position
    if (true) {
        
    }
    return false;
}