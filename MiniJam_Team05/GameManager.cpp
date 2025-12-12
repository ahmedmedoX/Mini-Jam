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
        Utilities::Convert_SFML_Box2D_Space(Vector2f(369, 100)));

    m_levelData.push_back({ [](b2World& world) {return make_unique<Level_Rock>(world);}});
    m_levelData.push_back({ [](b2World& world) {return make_unique<Level_Lava>(world);}});
    m_levelData.push_back({ [](b2World& world) {return make_unique<Level_Forest>(world);}});

    m_deltaTime = 0.0f;

    dir = Direction::NOMOVE;
    control = Control::NONE;

    m_world->SetContactListener(player.get());

    m_currentIndex = 0;
    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);

    MenuUI = new MainMenu();
    DeathUI = new DeadScreen();
    WinUI = new WinScreen();
    FinalUI = new FinalMenu();

    state = MENU;
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
        if (event.type == Event::Closed) {
            SoundManager::Instance().StopAll();
            m_window.close();
        }
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
    //if (Keyboard::isKeyPressed(Keyboard::R)) {
    //    RestartLevel();
    //}
    //if (Keyboard::isKeyPressed(Keyboard::N)) {
    //    int next = (m_currentIndex + 1) % m_levelData.size();
    //    SwitchLevel(next);
    //}
}

void GameManager::Update() {
    switch (state) {
        case (MENU): {
            MenuUI->Update(m_window, m_deltaTime);
            state = MenuUI->GetState();
            m_deltaTime = m_deltaClock.restart().asSeconds();
            m_rotationClock.restart();
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
            SoundManager::Instance().Stop("Level_Music");
            DeathUI->Update(m_window);
            DeathUI->Play();
            state = DeathUI->GetState();
            if (restart && (state == MENU)) {
                RestartLevel();
                MenuUI->Reset();
                DeathUI->Reset();
                restart = false;
            }
            if (restart && (state == RESTART)) {
                RestartLevel();
                DeathUI->Reset();
                restart = false;
            }
            break;
        }
        case (NEXT): {
            state = PLAY;
            restart = true;
            break;
        }
        case (WIN): {
            WinUI->Update(m_window);
            WinUI->Play();
            state = WinUI->GetState();
            if (restart && (state == RESTART)) {
                RestartLevel();
                WinUI->Reset();
                restart = false;
            }
            if (restart && (state == NEXT)) {
                SwitchLevel(m_currentIndex + 1);
                RestartLevel();
                WinUI->Reset();
                restart = false;
            }
            break;
        }
        case (RESTART): {
            state = PLAY;
            restart = true;
            break;
        }
        case (FINAL): {
            SoundManager::Instance().Stop("Level_Music");
            FinalUI->Update(m_window, m_deltaTime);
            state = FinalUI->GetState();
            if (restart && (state == MENU)) {
                RestartLevel();
                FinalUI->Reset();
                MenuUI->Reset();
                restart = false;
            }
            if (restart && (state == QUIT)) {
                RestartLevel();
                FinalUI->Reset();
                restart = false;
            }
            break;
        }
        case (QUIT): {
            SoundManager::Instance().StopAll();
            m_window.close();
            break;
        }
        default:
            break;
    }
}

void GameManager::Draw() {
    m_window.clear(Color::Black);
    switch (state) {
        case (MENU): {
            MenuUI->Draw(m_window);
            break;
        }
        case (PLAY): {
            if (m_currentLevel)
                m_currentLevel->Draw(m_window);
            m_window.draw(*player.get());
            break;
        }
        case (DEATH): {
            if (m_currentLevel)
                m_currentLevel->Draw(m_window);
            m_window.draw(*player.get());
            DeathUI->Death(m_window, m_deltaTime, player->GetPosition());
            break;
        }
        case (WIN): {
            if (m_currentLevel)
                m_currentLevel->Draw(m_window);
            m_window.draw(*player.get());
            WinUI->Draw(m_window);
            break;
        }
        case (FINAL): {
            if (m_currentLevel)
                m_currentLevel->Draw(m_window);
            m_window.draw(*player.get());
            FinalUI->Draw(m_window);
            break;
        }
        case (QUIT): {
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
        cout << m_currentIndex;
        //m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);
        m_deltaClock.restart();
        m_rotationClock.restart();
    }
}

void GameManager::RestartLevel() {
    //m_world = std::make_unique<b2World>(b2Vec2(0.f, -9.8f));
    srand(time(0));

    m_world->SetContactListener(nullptr);

    m_currentLevel = m_levelData[m_currentIndex].factory(*m_world);

    player.reset();
    switch (m_currentIndex)
    {
    case(0): {
        player = std::make_unique<Player>(*m_world,
            Utilities::Convert_SFML_Box2D_Space(Vector2f(369, 100)));
        break;
    }
    case(1): {
        player = std::make_unique<Player>(*m_world,
            Utilities::Convert_SFML_Box2D_Space(Vector2f(364, 100)));
        break;
    }
    case(2): {
        player = std::make_unique<Player>(*m_world,
            Utilities::Convert_SFML_Box2D_Space(Vector2f(270, 100)));
        break;
    }
    }

    m_world->SetContactListener(player.get());

    m_deltaClock.restart();
    m_rotationClock.restart();
}

void GameManager::CheckLevelLose() {
    if (player->isPlayerLost()) {
        state = DEATH;
        restart = true;
    }
}

void GameManager::CheckLevelWin() {
    if (player->isKeyCollected()) {
        m_currentLevel->CollectKey();
        if (player->isDoorOpened()) {
            if (m_currentIndex == m_levelData.size()-1)
                state = FINAL;
            else
                state = WIN;
        }
    }
}

GameManager::~GameManager() {}