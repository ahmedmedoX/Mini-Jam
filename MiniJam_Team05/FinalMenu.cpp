#include "FinalMenu.h"

FinalMenu::FinalMenu() {
    MenuBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Menu),
        { (Utilities::WINDOW_WIDTH * 1 / 4), (Utilities::WINDOW_HEIGHT * 3 / 4) + 40 },
        { 550 * 0.45f, 165 * 0.45f });

    QuitBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Quit),
        { (Utilities::WINDOW_WIDTH * 3 / 4), (Utilities::WINDOW_HEIGHT * 3 / 4) + 40 },
        { 550 * 0.45f, 165 * 0.45f });

    Background.setSize(Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
    Background.setFillColor(Color(0, 0, 0, 200));

    Text.setSize(Vector2f(464, 64));
    Text.setOrigin(Vector2f(464 / 2, 64 / 2));
    Text.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, 500));
    Text.setTexture(&SpriteLoader::getTexture(SpriteType::Win_Text));

    texture = &SpriteLoader::getTexture(SpriteType::keyIdle);
    key_Anim = Animation(texture, { 5, 1 }, 0.25);
    Key.setTexture(*texture);
    Key.setOrigin(16.0f, 16.0f);
    Key.setScale(128.0f / key_Anim.uvRect.width, 128.0f / key_Anim.uvRect.height);
    Key.setPosition(Vector2f(Utilities::WINDOW_WIDTH / 2, 300));

    MenuBtn.SetOnClick(std::bind(&FinalMenu::MenuBtnClicked, this));
    QuitBtn.SetOnClick(std::bind(&FinalMenu::QuitBtnClicked, this));
    state = FINAL;

    SoundManager::Instance().LoadSound("Final_Music", "assets/Audio/[You Wouldnt Be Here] Without Us.mp3");
    SoundManager::Instance().SetLoop("Final_Music", true);
}

void FinalMenu::Update(RenderWindow& window, const float deltaTime) {
    if (Play_Music) {
        SoundManager::Instance().Play("Final_Music");
        Play_Music = false;
    }

    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

    QuitBtn.Update(mouse);
    QuitBtn.OnClick(mouse);

    MenuBtn.Update(mouse);
    MenuBtn.OnClick(mouse);

    key_Anim.Update(0, deltaTime);
    Key.setScale(128.0f / key_Anim.uvRect.width, 128.0f / key_Anim.uvRect.height);
    Key.setTextureRect(key_Anim.uvRect);
}

void FinalMenu::Draw(RenderWindow& window) {
    window.draw(Background);
    window.draw(Text);
    window.draw(Key);
    MenuBtn.Draw(window);
    QuitBtn.Draw(window);
}

void FinalMenu::MenuBtnClicked() {
    SoundManager::Instance().Stop("Final_Music");
    state = MENU;
}

void FinalMenu::QuitBtnClicked() {
    state = QUIT;
}

GameState FinalMenu::GetState() {
    return state;
}

void FinalMenu::Reset() {
    SoundManager::Instance().Stop("Final_Music");
    Play_Music = true;
    state = FINAL;
}

FinalMenu::~FinalMenu() {}