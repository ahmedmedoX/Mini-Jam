#include "DeadScreen.h"

DeadScreen::DeadScreen() {
    SoundManager::Instance().LoadSound("death_Audio", "assets/Audio/death-sound.mp3");
    RestartBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Restart),
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 - 100 },
        { 550 * 0.75f, 165 * 0.75f });

    MenuBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Menu),
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 + 100 },
        { 550 * 0.75f, 165 * 0.75f });

    RestartBtn.SetOnClick(std::bind(&DeadScreen::RestartBtnClicked, this));
    MenuBtn.SetOnClick(std::bind(&DeadScreen::MenuBtnClicked, this));

    Background.setSize(Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
    Background.setFillColor(Color(0, 0, 0, 200));

    MaskTexture.create(1800, 1800);
    MaskTexture.clear(Color(0, 0, 0, 100));

    Mask.setRadius(200);
    Mask.setFillColor(Color::Transparent);
    Mask.setOrigin(200, 200);

    state = DEATH;
    TotalTime = 0.0f;
}

void DeadScreen::Play() {
    if(play)
        SoundManager::Instance().Play("death_Audio");
    play = false;
}

void DeadScreen::Death(RenderWindow& window, const float deltaTime,
    const Vector2f Position) {
    if (TotalTime < 5.0f) {
        float Scale = powf(2.0f, -10.0f * (TotalTime / 5.0f)) * 4.0f;
        Mask.setScale(Vector2f(Scale, Scale));
        TotalTime += deltaTime;
        MaskTexture.clear();
        Mask.setPosition(Position);
        MaskTexture.draw(Mask, sf::BlendNone);
        MaskTexture.display();
        DeathUI.setTexture(MaskTexture.getTexture());
        DeathUI.setColor(Color(255, 255, 255, 200));
        window.draw(DeathUI);
    }
    else {
        window.draw(Background);
        RestartBtn.Draw(window);
        MenuBtn.Draw(window);
    }
}

void DeadScreen::Update(RenderWindow& window) {
    if (!(TotalTime < 5.0f)) {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

        MenuBtn.Update(mouse);
        MenuBtn.OnClick(mouse);

        RestartBtn.Update(mouse);
        RestartBtn.OnClick(mouse);
    }
}

void DeadScreen:: MenuBtnClicked() {
    state = MENU;
}

void DeadScreen::RestartBtnClicked() {
    state = RESTART;
}

GameState DeadScreen::GetState() {
    return state;
}

void DeadScreen::Reset() {
    state = DEATH;
    TotalTime = 0.0f;
    play = true;
}

DeadScreen::~DeadScreen() {}