#include "MainMenu.h"

MainMenu::MainMenu() {
    StartBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Start),
        { (Utilities::WINDOW_WIDTH * 3 / 4) + 20, (Utilities::WINDOW_HEIGHT * 3 / 4) - 50 },
        { 550 * 0.45f, 165 * 0.45f });

    QuitBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Quit),
        { (Utilities::WINDOW_WIDTH * 3 / 4) + 20, (Utilities::WINDOW_HEIGHT * 3 / 4) + 40 },
        { 550 * 0.45f, 165 * 0.45f });

    Background.setSize(Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
    Background.setTexture(&SpriteLoader::getTexture(SpriteType::SplashScreen));
    Background.setFillColor(Color(255, 255, 255, 0));

    StartBtn.SetOnClick(std::bind(&MainMenu::StartBtnClicked, this));
    QuitBtn.SetOnClick(std::bind(&MainMenu::QuitBtnClicked, this));
    state = MENU;

    SoundManager::Instance().LoadSound("MainMenu_Music", "assets/Audio/xXTFCNSTheArcade24bitXx.mp3");
    SoundManager::Instance().SetLoop("MainMenu_Music", true);
    SoundManager::Instance().Play("MainMenu_Music");
}

void MainMenu::Update(RenderWindow& window, const float deltaTime) {
    if (TotalTime < 10.0f) {
        float fade = 0.0f;
        float t = TotalTime;
        if ((t /= 10.0f / 2) < 1)
            fade = ((255.0f / 2) * (t * t));
        else
            fade = -255.0f / 2 * (((t - 2) * (--t)) - 1);
        TotalTime += deltaTime;
        Background.setFillColor(Color(255, 255, 255, fade));
    }
    else {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        QuitBtn.Update(mouse);
        QuitBtn.OnClick(mouse);
        StartBtn.Update(mouse);
        StartBtn.OnClick(mouse);
    }
}

void MainMenu::Draw(RenderWindow& window) {
    window.draw(Background);
    if (TotalTime >= 10.0f) {
        StartBtn.Draw(window);
        QuitBtn.Draw(window);
    }
}

void MainMenu::StartBtnClicked() {
    state = PLAY;
    SoundManager::Instance().Stop("MainMenu_Music");
}

void MainMenu::QuitBtnClicked() {
    state = QUIT;
}

GameState MainMenu::GetState() {
    return state;
}

void MainMenu::Reset() {
    SoundManager::Instance().Play("MainMenu_Music");
    TotalTime = 0.0f;
    Background.setFillColor(Color(0, 0, 0, 0));
    state = MENU;
}

MainMenu::~MainMenu() {}