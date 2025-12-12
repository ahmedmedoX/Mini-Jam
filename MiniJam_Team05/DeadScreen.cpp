#include "DeadScreen.h"

DeadScreen::DeadScreen() {
    SoundManager::Instance().LoadSound("deathsound", "assets/Audio/death-sound.mp3");
    SoundManager::Instance().Play("deathsound");

    RestartBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Restart),
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 - 100 },
        { 550 * 0.75f, 165 * 0.75f });

    MenuBtn = UIBtn(&SpriteLoader::getTexture(SpriteType::Menu),
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 + 100 },
        { 550 * 0.75f, 165 * 0.75f });

    RestartBtn.SetOnClick(std::bind(&DeadScreen::RestartBtnClicked, this));
    MenuBtn.SetOnClick(std::bind(&DeadScreen::MenuBtnClicked, this));

    Background.setSize(Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
    Background.setFillColor(Color(0, 0, 0, 100));
}

void DeadScreen::Update(RenderWindow& window) {
	Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));

	MenuBtn.Update(mouse);
	MenuBtn.OnClick(mouse);

    RestartBtn.Update(mouse);
    RestartBtn.OnClick(mouse);
}

void DeadScreen::Draw(RenderWindow& window) {
	window.draw(Background);
    RestartBtn.Draw(window);
	MenuBtn.Draw(window);
}

void DeadScreen:: MenuBtnClicked() {
	std::cout << "menu!\n";
}

void DeadScreen::RestartBtnClicked() {
	std::cout << "restarted!\n";
}