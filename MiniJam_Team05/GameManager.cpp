#include "GameManager.h"

GameManager::GameManager()
    : m_window(VideoMode(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT),
        "Glitch Bound", Style::Close)
{
    Image* icon = new Image();
    icon->loadFromFile(FilePathes::icon);

    m_window.setFramerateLimit(Utilities::FPS);
    m_window.setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
    
    m_world = make_unique<b2World>(b2Vec2(0, -10.0f));

    player = std::make_unique<Player>(*m_world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 400)));

    m_levelData.push_back({ [](b2World& world) {return make_unique<Level_Rock>(world);}});
    m_levelData.push_back({ [](b2World& world) {return make_unique<Level_Lava>(world);}});
    m_levelData.push_back({ [](b2World& world) {return make_unique<Level_Forest>(world);}});

    m_deltaTime = 0.f;

    dir = Direction::NOMOVE;
    control = Control::NONE;

    m_world->SetContactListener(player.get());

    m_currentIndex = 0;
    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);

    mainMenu = new MainMenu(m_window);
    state = MENU;
    //deadScreen = new DeadScreen();
}

void GameManager::Run() {
    while (m_window.isOpen()) {
        HandleInput();
        Update();
        Draw();
        CheckLevelWin();
        CheckLevelLose();
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
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                dir = Direction::LEFT;
            } else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                dir = Direction::RIGHT;
            }
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D ||
                event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
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
    switch (state) {
        case (MENU): {
            if (mainMenu->StartGame())
                state = PLAY;
            mainMenu->Update(m_window);
            break;
        }
        case (PLAY): {
            if (m_deltaClock.getElapsedTime().asSeconds() > timeStep) {
                m_world->Step(timeStep, velocityIterations, positionIterations);
                m_deltaTime = m_deltaClock.restart().asSeconds();
            }
            if (m_currentLevel)
                m_currentLevel->Update(m_deltaTime, m_rotationClock, *m_world);
            if (player)
                player->Update(dir, control, m_deltaTime);
            break;
        }
        case (DEATH): {
            deadScreen->Update(m_window);
            Death();
            break;
        }
        case (WIN): {
            Win();
            break;
        }
        default:
            break;
    }
}

void GameManager::Draw() {
    m_window.clear();
    switch (state) {
        case (MENU): {
            mainMenu->Draw(m_window);
            break;
        }
        case (PLAY): {
            if (m_currentLevel)
                m_currentLevel->Draw(m_window);
            m_window.draw(*player.get());
            break;
        }
        case (DEATH): {
            deadScreen->Draw(m_window);
            Death();
            break;
        }
        case (WIN): {
            Win();
            break;
        }
        default:
            break;
    }
    m_window.display();
}

void GameManager::SwitchLevel(const int index) {
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
    player = std::make_unique<Player>(*m_world,
        Utilities::Convert_SFML_Box2D_Space(Vector2f(400, 400)));

    m_world->SetContactListener(player.get());

    m_deltaClock.restart();
    m_rotationClock.restart();
}

void GameManager::CheckLevelLose() {
    if (player->isPlayerLost())
        state = DEATH;
}

void GameManager::CheckLevelWin() {
    if (player->isKeyCollected()) {
        m_currentLevel->CollectKey();
        if (player->isDoorOpened()) {
            int next = (m_currentIndex + 1) % m_levelData.size();
            SwitchLevel(next);
            RestartLevel();
        }
    }
}

void GameManager::Win() {
    // TODO: Replace with actual level win logic
    // Example: if player box reaches some position
    cout << "WIN\n";
}

void GameManager::Death() {
    //if (TotalTime < 5.0f) {
    //    if ((TotalTime /= 5.0f / 2) < 1) {
    //        Scale = ((5.0f / 2) * (TotalTime * TotalTime));
    //    }
    //    else {
    //        Scale = -5.0f / 2 * (((TotalTime - 2) * (--TotalTime)) - 1);
    //    }
    //    Win_Screen.setScale(Vector2f(Scale, Scale));
    //}
    RestartLevel();
    state = PLAY;
}

GameManager::~GameManager() {}