#include "MainMenu.h"

MainMenu::MainMenu(RenderWindow& m_window) {
    window = &m_window;

    StartBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Start),
        { (Utilities::WINDOW_WIDTH * 3 / 4) + 20, (Utilities::WINDOW_HEIGHT * 3 / 4) - 50 },
        { 550 * 0.45f, 165 * 0.45f });

    QuitBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Quit),
        { (Utilities::WINDOW_WIDTH * 3 / 4) + 20, (Utilities::WINDOW_HEIGHT * 3 / 4) + 40 },
        { 550 * 0.45f, 165 * 0.45f });

    Background.setSize(Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
    Background.setTexture(&SpriteLoader::getTexture(SpriteType::SplashScreen));

    StartBtn.SetOnClick(std::bind(&MainMenu::StartBtnClicked, this));
    QuitBtn.SetOnClick(std::bind(&MainMenu::QuitBtnClicked, this));
}

MainMenu::~MainMenu() {}

void MainMenu::Update(RenderWindow& window) {
    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

    QuitBtn.Update(mouse);
    QuitBtn.OnClick(mouse);

    StartBtn.Update(mouse);
    StartBtn.OnClick(mouse);
}

void MainMenu::Draw(RenderWindow& window) {
    window.draw(Background);
    StartBtn.Draw(window);
    QuitBtn.Draw(window);
}

void MainMenu::StartBtnClicked() {
    std::cout << "start!\n";
    GameStarted = true;
}

void MainMenu::QuitBtnClicked() {
    window->close();
}

bool MainMenu::StartGame() {
    return GameStarted;
}