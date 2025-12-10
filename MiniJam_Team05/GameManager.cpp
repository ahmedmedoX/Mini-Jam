#include "GameManager.h"

GameManager::GameManager()
    : m_window(VideoMode(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT), "SFML Box2D Physics!")
{
    m_window.setFramerateLimit(Utilities::FPS);

    m_world = make_unique<b2World>(b2Vec2(0, -9.8f));

    player = std::make_unique<Player>(
        *m_world, Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 400)));

    Texture* bgTexture =new Texture();
    bgTexture->loadFromFile("Map.jfif");

    m_levelData.push_back({
        [bgTexture](b2World& world) {
            return make_unique<Level_Rock>(world, bgTexture);
        }
        });

    m_levelData.push_back({
        [bgTexture](b2World& world) {
            return make_unique<Level_Forest>(world, bgTexture);
        }
        });

    m_deltaTime = 0.f;

    dir = Direction::NOMOVE;
    control = Control::NONE;

    m_world->SetContactListener(player.get());

    m_currentIndex = 0;
    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);
}

GameManager::~GameManager() {}

void GameManager::Run() {
    while (m_window.isOpen()) {
        HandleInput();
        Update();
        Draw();
        CheckLevelWin();
        //if (CheckLevelWin()) {
        //    if (m_currentIndex >= m_levelData.size()) {
        //        Win();
        //        return;
        //    }
        //    m_currentIndex++;
        //    SwitchLevel(m_currentIndex);
        //}
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
    //if (Keyboard::isKeyPressed(Keyboard::N)) {
    //    int next = (m_currentIndex + 1) % m_levelData.size();
    //    SwitchLevel(next);
    //}
}

void GameManager::Update() {
    if (m_deltaClock.getElapsedTime().asSeconds() > timeStep) {
        m_world->Step(timeStep, velocityIterations, positionIterations);
        m_deltaTime = m_deltaClock.restart().asSeconds();
    }
    //lvl->Update(m_deltaTime, m_rotationClock, *m_world);

    if (m_currentLevel)
        m_currentLevel->Update(m_deltaTime, m_rotationClock, *m_world);

    if (player)
     player->Update(dir, control, m_deltaTime);
}

void GameManager::Draw() {
    m_window.clear();

    if (m_currentLevel)
        m_currentLevel->Draw(m_window);

    //lvl->Draw(m_window);

    m_window.draw(*player.get());
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
    m_world->SetContactListener(nullptr);

    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);

    player.reset();
    player = std::make_unique<Player>(
        *m_world, Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 400)));

    m_world->SetContactListener(player.get());

    m_deltaClock.restart();
    m_rotationClock.restart();
}

bool GameManager::CheckLevelWin() {
    Player* p = player.get();

    if (!p->isKeyCollected())
        return false;

    m_currentLevel->CollectKey();

    if (p->isDoorOpened()) {
        int next = (m_currentIndex + 1) % m_levelData.size();
        SwitchLevel(next);
        RestartLevel();
    }

    return false;
}

void GameManager::Win() {
    // TODO: Replace with actual level win logic
    // Example: if player box reaches some position

}

void GameManager::Death() {

}