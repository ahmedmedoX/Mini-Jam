#include "WinScreen.h"

WinScreen::WinScreen() {
    SoundManager::Instance().LoadSound("win_Audio", "assets/Audio/win-sound.mp3");

    RestartBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Restart),
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 + 100 },
        { 550 * 0.75f, 165 * 0.75f });

    NextBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Next),
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 - 100 },
        { 550 * 0.75f, 165 * 0.75f });

    Background.setSize(Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
    Background.setFillColor(Color(0, 0, 0, 200));

    RestartBtn.SetOnClick(std::bind(&WinScreen::RestartBtnClicked, this));
    NextBtn.SetOnClick(std::bind(&WinScreen::NextBtnClicked, this));
    state = WIN;
}

void WinScreen::Play() {
    if (play)
        SoundManager::Instance().Play("win_Audio");
    play = false;
}

void WinScreen::Update(RenderWindow& window) {
    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

    NextBtn.Update(mouse);
    NextBtn.OnClick(mouse);

    RestartBtn.Update(mouse);
    RestartBtn.OnClick(mouse);
}

void WinScreen::Draw(RenderWindow& window) {
    window.draw(Background);
    RestartBtn.Draw(window);
    NextBtn.Draw(window);
}

void WinScreen::NextBtnClicked() {
    state = NEXT;
}

void WinScreen::RestartBtnClicked() {
    state = RESTART;
}

GameState WinScreen::GetState() {
    return state;
}

void WinScreen::Reset() {
    state = WIN;
    play = true;
}

WinScreen::~WinScreen() {}