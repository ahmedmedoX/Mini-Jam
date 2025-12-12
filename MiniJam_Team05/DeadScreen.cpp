#include "DeadScreen.h"

DeadScreen::DeadScreen(sf::Window& window) {
    RetryTexture.loadFromFile("assets/ui/RestartBotton.png");
    MenuTexture.loadFromFile("assets/ui/MenuButton.png");

    SoundManager::Instance().LoadSound("deathsound", "assets/Audio/death-sound.mp3");
    SoundManager::Instance().Play("deathsound");

    RetryBtn = UIBtn(&RetryTexture,
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 - 100 },
        { 550 * 0.75f, 165 * 0.75f });

    MenuBtn = UIBtn(&MenuTexture,
        { Utilities::WINDOW_WIDTH / 2, Utilities::WINDOW_HEIGHT / 2 + 100 },
        { 550 * 0.75f, 165 * 0.75f });

    RetryBtn.SetOnClick(std::bind(&DeadScreen::RestartBtnClicked, this));
    MenuBtn.SetOnClick(std::bind(&DeadScreen::MenuBtnClicked, this));
}

void DeadScreen::Update(sf::RenderWindow& window) {
	sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	MenuBtn.Update(mouse);
	MenuBtn.OnClick(mouse	);

	RetryBtn.Update(mouse);
	RetryBtn.OnClick(mouse);
}

void DeadScreen::Draw(sf::RenderWindow& window) {
    sf::RectangleShape background(sf::Vector2f(Utilities::WINDOW_WIDTH, Utilities::WINDOW_HEIGHT));
	background.setPosition(0, 0);
    background.setFillColor(sf::Color(0, 0, 0, 100));

	window.draw(background);
	RetryBtn.Draw(window);
	MenuBtn.Draw(window);
}

void DeadScreen:: MenuBtnClicked() {
	std::cout << "menue!\n";
}
void DeadScreen::RestartBtnClicked() {
	std::cout << "restated!\n";
}